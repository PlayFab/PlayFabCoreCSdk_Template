// Copyright (C) Microsoft Corporation. All rights reserved.

#include "TestAppPch.h"

#include "TestAppGDK.h"
#include "TestApp.h"
#include "ATGColors.h"
#include "FindMedia.h"
#include "StringUtil.h"
#include <XGameErr.h>

extern void ExitSample();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Sample* g_Sample = nullptr;

namespace
{
    const int c_sampleUIPanel = 2000;
}

Sample::Sample() noexcept(false) :
    m_frame(0),
    m_asyncQueue(nullptr)
{
    g_Sample = this;

    DX::ThrowIfFailed(
        XTaskQueueCreate(XTaskQueueDispatchMode::ThreadPool, XTaskQueueDispatchMode::Manual, &m_asyncQueue)
    );

    // Renders only 2D, so no need for a depth buffer.
    m_deviceResources = std::make_unique<DX::DeviceResources>(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_UNKNOWN);

    ATG::UIConfig uiconfig;
    m_ui = std::make_shared<ATG::UIManager>(uiconfig);
    m_log = std::make_unique<DX::TextConsoleImage>();
}

Sample::~Sample()
{
    if (m_deviceResources)
    {
        m_deviceResources->WaitForGpu();
    }

    if (m_asyncQueue)
    {
        XTaskQueueCloseHandle(m_asyncQueue);
        m_asyncQueue = nullptr;
    }
}

// Initialize the Direct3D resources required to run.
void Sample::Initialize(HWND window, int width, int height)
{
    m_gamePad = std::make_unique<GamePad>();

    m_keyboard = std::make_unique<Keyboard>();

    m_mouse = std::make_unique<Mouse>();
#ifdef _GAMING_DESKTOP
    m_mouse->SetWindow(window);
#endif


#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
    // NOTE: When running the app from the Start Menu (required for
    //    Store API's to work) the Current Working Directory will be
    //    returned as C:\Windows\system32 unless you overwrite it.
    //    The sample relies on the font and image files in the .exe's
    //    directory and so we do the following to set the working
    //    directory to what we want.
    char dir[1024];
    GetModuleFileNameA(NULL, dir, 1024);
    std::string exe = dir;
    exe = exe.substr(0, exe.find_last_of("\\"));
    SetCurrentDirectoryA(exe.c_str());
#endif

    m_ui->LoadLayout(L".\\Assets\\SampleUI.csv", L".\\Assets");

    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    uint32_t titleId = 0;
    HRESULT hr = XGameGetXboxTitleId(&titleId);
    if (FAILED(hr))
    {
        m_log->WriteLine(L"Can not get title ID.  Ensure you are running inside a app package");
    }

    SetupUI();
}

void Sample::RunTests()
{
    if (!m_testsStarted && m_log)
    {
        m_testsStarted = true;
        m_log->Clear();
        m_log->WriteLine(L"Running tests");

        CreateThread(nullptr, 0, [](LPVOID) -> DWORD
            {
                PlayFabUnit::TestApp testApp;
                auto result = testApp.Main();

                g_Sample->m_testsCompleted = true;

                return result;
            },
            nullptr, 0, nullptr);
    }
}


#pragma region UI Methods
void Sample::SetupUI()
{
    using namespace ATG;

}

#pragma endregion

#pragma region Frame Update
// Executes basic render loop.
void Sample::Tick()
{
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Frame %I64u", m_frame);

    m_timer.Tick([&]()
        {
            Update(m_timer);
        });

    Render();

    PIXEndEvent();
    m_frame++;
}

// Updates the world.
void Sample::Update(DX::StepTimer const& timer)
{
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Update");
    float elapsedTime = float(timer.GetElapsedSeconds());

    // Auto start tests after a small delay
    m_startTimer -= elapsedTime;
    if (m_startTimer < 0.0f && !m_testsStarted)
    {
        RunTests();
    }

    if (m_testsCompleted)
    {
        //ExitSample();
    }

    auto pad = m_gamePad->GetState(0);
    if (pad.IsConnected())
    {
        m_gamePadButtons.Update(pad);

        if (pad.IsViewPressed())
        {
            ExitSample();
        }

        m_ui->Update(elapsedTime, pad);
    }
    else
    {
        m_gamePadButtons.Reset();
    }

    auto kb = m_keyboard->GetState();
    m_keyboardButtons.Update(kb);

    if (kb.Enter || kb.Space || kb.B)
    {
        RunTests();
    }
    if (kb.A)
    {
        RunTests();
    }
    if (kb.Escape)
    {
        ExitSample();
    }

    // Process any completed tasks
    while (XTaskQueueDispatch(m_asyncQueue, XTaskQueuePort::Completion, 0))
    {
    }

    PIXEndEvent();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Sample::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    // Prepare the command list to render a new frame.
    m_deviceResources->Prepare();
    Clear();

    auto commandList = m_deviceResources->GetCommandList();
    PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Render");

    ID3D12DescriptorHeap* heap = m_resourceDescriptors->Heap();
    commandList->SetDescriptorHeaps(1, &heap);

    if (m_log)
    {
        m_log->Render(commandList);
    }
    if (m_ui)
    {
        m_ui->Render(commandList);
    }

    PIXEndEvent(commandList);

    // Show the new frame.
    PIXBeginEvent(m_deviceResources->GetCommandQueue(), PIX_COLOR_DEFAULT, L"Present");
    m_deviceResources->Present();
    m_graphicsMemory->Commit(m_deviceResources->GetCommandQueue());
    PIXEndEvent(m_deviceResources->GetCommandQueue());
}

// Helper method to clear the back buffers.
void Sample::Clear()
{
    auto commandList = m_deviceResources->GetCommandList();
    PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Clear");

    // Clear the views.
    auto rtvDescriptor = m_deviceResources->GetRenderTargetView();

    commandList->OMSetRenderTargets(1, &rtvDescriptor, FALSE, nullptr);
    commandList->ClearRenderTargetView(rtvDescriptor, ATG::Colors::Background, 0, nullptr);

    // Set the viewport and scissor rect.
    auto viewport = m_deviceResources->GetScreenViewport();
    auto scissorRect = m_deviceResources->GetScissorRect();
    commandList->RSSetViewports(1, &viewport);
    commandList->RSSetScissorRects(1, &scissorRect);

    PIXEndEvent(commandList);
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Sample::OnActivated()
{
}

void Sample::OnDeactivated()
{
}

void Sample::OnSuspending()
{
    m_deviceResources->Suspend();
}

void Sample::OnResuming()
{
    m_deviceResources->Resume();
    m_timer.ResetElapsedTime();
    m_gamePadButtons.Reset();
    m_keyboardButtons.Reset();
    m_ui->Reset();
    m_log.reset();
}

void Sample::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Sample::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();
}

// Properties
void Sample::GetDefaultSize(int& width, int& height) const
{
    width = 1920;
    height = 1080;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Sample::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    m_graphicsMemory = std::make_unique<GraphicsMemory>(device);

    RenderTargetState rtState(m_deviceResources->GetBackBufferFormat(), m_deviceResources->GetDepthBufferFormat());

    ResourceUploadBatch resourceUpload(device);
    resourceUpload.Begin();

    m_resourceDescriptors = std::make_unique<DirectX::DescriptorPile>(device,
        D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
        D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
        Descriptors::Count,
        Descriptors::Reserve
        );

    m_log->RestoreDevice(
        device,
        resourceUpload,
        rtState,
        L"Media\\Fonts\\SegoeUI_18.spritefont",
        L"Assets\\ATGSampleBackground.DDS",
        m_resourceDescriptors->GetCpuHandle(Descriptors::Font),
        m_resourceDescriptors->GetGpuHandle(Descriptors::Font),
        m_resourceDescriptors->GetCpuHandle(Descriptors::Background),
        m_resourceDescriptors->GetGpuHandle(Descriptors::Background)
    );

    m_ui->RestoreDevice(device, rtState, resourceUpload, *m_resourceDescriptors);

    auto uploadResourcesFinished = resourceUpload.End(m_deviceResources->GetCommandQueue());
    uploadResourcesFinished.wait();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Sample::CreateWindowSizeDependentResources()
{
    auto viewport = m_deviceResources->GetScreenViewport();
    static const RECT screenDisplay = { 50, 150, static_cast<LONG>(viewport.Width - 50), static_cast<LONG>(viewport.Height - 150) };
    m_log->SetWindow(screenDisplay, false);
    m_log->SetViewport(viewport);

    RECT size = m_deviceResources->GetOutputSize();
    m_ui->SetWindow(size);
}

void Sample::OnDeviceLost()
{
    m_graphicsMemory.reset();
    m_resourceDescriptors.reset();
}

void Sample::OnDeviceRestored()
{
    CreateDeviceDependentResources();
    CreateWindowSizeDependentResources();
}
#pragma endregion

namespace PlayFabUnit
{

void TestApp::Log(_Printf_format_string_ char const* format, ...)
{
    static char message[1024 * 64];

    va_list varArgs{};
    va_start(varArgs, format);
    vsprintf_s(message, format, varArgs);
    va_end(varArgs);

    if (g_Sample && g_Sample->m_log != nullptr)
    {
        std::wstring wstr = DX::Utf8ToWide(message);
        g_Sample->m_log->WriteLine(wstr.c_str());
    }
    else
    {
        std::cout << message;
        std::cout << "\n";
    }
}

// Partial class implementation of TestApp.
// Each platform gets its own file and implementation of the following methods, since the logic
// is likely to be very different on all of them.
bool TestApp::LoadTitleDataJson(std::shared_ptr<char*>& testDataJson, size_t& testDataJsonLen)
{
    // Read the title data from the file into the output character array.
    std::ifstream titleDataFile;
    titleDataFile.open("TestTitle.json", std::ios::binary | std::ios::in);

    if (!titleDataFile)
    {
        return false;
    }

    std::streampos begin = titleDataFile.tellg();
    titleDataFile.seekg(0, std::ios::end);
    std::streampos end = titleDataFile.tellg();
    testDataJsonLen = static_cast<int>(end - begin);
    testDataJson = std::make_shared<char*>(new char[testDataJsonLen + 1]);

    titleDataFile.seekg(0, std::ios::beg);
    titleDataFile.read(*testDataJson, testDataJsonLen);
    (*testDataJson)[testDataJsonLen] = '\0';

    titleDataFile.close();

    return true;
}

void TestApp::SetTraceLevel(PFTestTraceLevel level)
{
    traceLevel = level;
}

bool TestApp::ShouldTrace(PFTestTraceLevel level)
{
    return (traceLevel > level);
}

void TestApp::LogPut(const char* message)
{
    Log(message);

    // Write to Visual Studio's Output window.
    OutputDebugStringA(message);
}
}