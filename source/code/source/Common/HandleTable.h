namespace PlayFab
{

using HANDLE = PFHandle;

// Simple handle table used to track and map open client handles 
template<typename T>
class HandleTable
{
public:
    HandleTable(HANDLE firstHandleValue);
    HandleTable(HandleTable const&) = delete;
    HandleTable(HandleTable&&) = delete;
    HandleTable& operator=(HandleTable const&) = delete;
    HandleTable& operator=(HandleTable&&) = delete;

    HRESULT MakeHandle(SharedPtr<T>&& object, HANDLE& handle);
    HRESULT FromHandle(HANDLE handle, SharedPtr<T>& object) const;
    void CloseHandle(HANDLE handle);

private:
    mutable std::mutex m_mutex;
    Map<HANDLE, SharedPtr<T>> m_handles;
    HANDLE m_nextHandle;
};

//------------------------------------------------------------------------------
// Template implementations
//------------------------------------------------------------------------------

template<typename T>
HandleTable<T>::HandleTable(HANDLE firstHandleValue) :
    m_nextHandle{ firstHandleValue }
{
}

template<typename T>
HRESULT HandleTable<T>::MakeHandle(SharedPtr<T>&& object, HANDLE& handle)
{
    std::unique_lock<std::mutex> lock{ m_mutex };
    RETURN_HR_IF(E_INVALIDARG, !object);

    handle = m_nextHandle++;
    m_handles.emplace(handle, std::move(object));

    return S_OK;
}

template<typename T>
HRESULT HandleTable<T>::FromHandle(HANDLE handle, SharedPtr<T>& object) const
{
    std::unique_lock<std::mutex> lock{ m_mutex };
    auto it = m_handles.find(handle);
    if (it == m_handles.end())
    {
        TRACE_ERROR("%s: Attempted to access invalid handle %llu", __FUNCTION__, handle);
        return E_INVALIDARG; // Could define E_PF_INVALIDHANDLE
    }

    assert(it->second);
    object = it->second;

    return S_OK;
}

template<typename T>
void HandleTable<T>::CloseHandle(HANDLE handle)
{
    std::unique_lock<std::mutex> lock{ m_mutex };

    auto it = m_handles.find(handle);
    if (it == m_handles.end())
    {
        TRACE_WARNING("%s: Attempted to close invalid handle %llu", __FUNCTION__, handle);
        return;
    }

    m_handles.erase(it);
}

}
