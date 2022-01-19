echo Running fetchTools.cmd

if EXIST "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\MSBuild\15.0\Bin\amd64\msbuild.exe" "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\MSBuild\15.0\Bin\amd64\msbuild.exe" /version
if EXIST "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\amd64\MSBuild.exe" "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\amd64\MSBuild.exe" /version
dir /b "C:\Program Files (x86)\Microsoft SDKs"
dir /b "C:\Program Files (x86)\Windows Kits\10\Include"
set

set patArg=%1
set sdkArg=%2
set externalBranchArg=%3
set buildToolsBranchArg=%4
cd /D %BUILD_STAGINGDIRECTORY%
call git clone https://anything:%patArg%@microsoft.visualstudio.com/DefaultCollection/Xbox.Services/_git/sdk.buildtools
cd sdk.buildtools
git reset --hard HEAD
if "%buildToolsBranchArg%" NEQ "" call git checkout %buildToolsBranchArg%
cd /D %BUILD_STAGINGDIRECTORY%
dir "%BUILD_STAGINGDIRECTORY%\sdk.buildtools\buildMachine

if "%sdkArg%" == "EXT" goto setupExt
goto skipExt
:setupExt
cd /D %BUILD_STAGINGDIRECTORY%
call git clone https://anything:%patArg%@microsoft.visualstudio.com/Xbox.Services/_git/sdk.external
cd sdk.external
git reset --hard HEAD
if "%externalBranchArg%" NEQ "" call git checkout %externalBranchArg%
cd /D %BUILD_STAGINGDIRECTORY%
dir "%BUILD_STAGINGDIRECTORY%\sdk.external\ExtractedGDK\"
:skipExt

