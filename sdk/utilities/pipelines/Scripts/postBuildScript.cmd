if "%1" == "local" goto testlocal
goto start

:testlocal
set BUILD_BINARIESDIRECTORY=%CD%\..\..\Bins
set BUILD_SOURCESDIRECTORY=%CD%\..\..

:start

echo Running postBuildScript.cmd
echo on

set

set SDK_DROP_LOCATION=%BUILD_BINARIESDIRECTORY%\SDK
rmdir /s /q %SDK_DROP_LOCATION%
mkdir %SDK_DROP_LOCATION%

setlocal

REM ------------------- VERSION SETUP BEGIN -------------------
call %BUILD_SOURCESDIRECTORY%\Utilities\Pipelines\Scripts\setBuildVersion.cmd

for /f "tokens=2 delims==" %%G in ('wmic os get localdatetime /value') do set datetime=%%G
set DATETIME_YEAR=%datetime:~0,4%
set DATETIME_MONTH=%datetime:~4,2%
set DATETIME_DAY=%datetime:~6,2%

echo BUILD_BUILDNUMBER = %BUILD_BUILDNUMBER%
FOR /F "TOKENS=4 eol=/ DELIMS=. " %%A IN ("%BUILD_BUILDNUMBER%") DO SET SDK_POINT_NAME_VER=%%A
set SDK_POINT_NAME_YEAR=%DATETIME_YEAR%
set SDK_POINT_NAME_MONTH=%DATETIME_MONTH%
set SDK_POINT_NAME_DAY=%DATETIME_DAY%      
set SDK_VERSION_NUMBER=%SDK_RELEASE_YEAR%.%SDK_RELEASE_MONTH%.%SDK_POINT_NAME_YEAR%%SDK_POINT_NAME_MONTH%%SDK_POINT_NAME_DAY%.%SDK_RELEASE_QFE%
set MINOR_VERSION_NUMBER=%SDK_POINT_NAME_YEAR%%SDK_POINT_NAME_MONTH%%SDK_POINT_NAME_DAY%%SDK_POINT_NAME_VER%

REM ------------------- HEADERS BEGIN -------------------
robocopy /NJS /NJH /MT:16 /S /NP %BUILD_SOURCESDIRECTORY%\include %SDK_DROP_LOCATION%\Include
robocopy /NJS /NJH /MT:16 /S /NP %BUILD_SOURCESDIRECTORY%\external\libHttpClient\Include %SDK_DROP_LOCATION%\include

REM ------------------- GDK BEGIN -------------------
set SDK_DROP_LOCATION_GDK=%SDK_DROP_LOCATION%\GDK
set SDK_DROP_LOCATION_GDK_BIN=%SDK_DROP_LOCATION_GDK%\c
mkdir %SDK_DROP_LOCATION_GDK%
mkdir %SDK_DROP_LOCATION_GDK_BIN%
mkdir %SDK_DROP_LOCATION_GDK_BIN%\include
mkdir %SDK_DROP_LOCATION_GDK_BIN%\binaries\GSDKXboxExtensionSDKs\release\v141
mkdir %SDK_DROP_LOCATION_GDK_BIN%\binaries\GSDKXboxExtensionSDKs\debug\v141
mkdir %SDK_DROP_LOCATION_GDK_BIN%\binaries\GSDKXboxExtensionSDKs\release\v142
mkdir %SDK_DROP_LOCATION_GDK_BIN%\binaries\GSDKXboxExtensionSDKs\debug\v142
mkdir %SDK_DROP_LOCATION_GDK_BIN%\binaries\GSDKDesktopExtensionSDKs\release\v141
mkdir %SDK_DROP_LOCATION_GDK_BIN%\binaries\GSDKDesktopExtensionSDKs\debug\v141
mkdir %SDK_DROP_LOCATION_GDK_BIN%\binaries\GSDKDesktopExtensionSDKs\release\v142
mkdir %SDK_DROP_LOCATION_GDK_BIN%\binaries\GSDKDesktopExtensionSDKs\debug\v142

copy %BUILD_SOURCESDIRECTORY%\Utilities\GDK\Xbox.Services.API.C.props %SDK_DROP_LOCATION_GDK_BIN%
copy %BUILD_SOURCESDIRECTORY%\Utilities\GDK\Xbox.Services.API.Classic.props %SDK_DROP_LOCATION_GDK_BIN%

robocopy /NJS /NJH /MT:16 /S /NP %SDK_DROP_LOCATION%\Include %SDK_DROP_LOCATION_GDK_BIN%\include
copy %BUILD_SOURCESDIRECTORY%\ThirdPartyNotices.txt %SDK_DROP_LOCATION_GDK_BIN%\include\pf-c
copy %BUILD_SOURCESDIRECTORY%\External\libHttpClient\ThirdPartyNotices.txt %SDK_DROP_LOCATION_GDK_BIN%\include\httpClient

set PLAT=Gaming.Xbox.x64
set PLAT_LAYOUT_NAME=GSDKXboxExtensionSDKs
set TYPE=release
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C\Microsoft.Xbox.Services.141.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C\Microsoft.Xbox.Services.141.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\Microsoft.Xbox.Services.141.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.142.GDK.C\Microsoft.Xbox.Services.142.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.142.GDK.C\Microsoft.Xbox.Services.142.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142\Microsoft.Xbox.Services.142.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.141.GDK.C\libHttpClient.141.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.141.GDK.C\libHttpClient.141.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\libHttpClient.141.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.142.GDK.C\libHttpClient.142.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.142.GDK.C\libHttpClient.142.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142\libHttpClient.141.GDK.C.lib.remove

set TYPE=debug
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C\Microsoft.Xbox.Services.141.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C\Microsoft.Xbox.Services.141.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\Microsoft.Xbox.Services.141.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.142.GDK.C\Microsoft.Xbox.Services.142.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.142.GDK.C\Microsoft.Xbox.Services.142.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142\Microsoft.Xbox.Services.142.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.141.GDK.C\libHttpClient.141.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.141.GDK.C\libHttpClient.141.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\libHttpClient.141.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.142.GDK.C\libHttpClient.142.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.142.GDK.C\libHttpClient.142.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142\libHttpClient.142.GDK.C.lib.remove

set PLAT=Gaming.Desktop.x64
set PLAT_LAYOUT_NAME=GSDKDesktopExtensionSDKs
set TYPE=release
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C\Microsoft.Xbox.Services.141.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C\Microsoft.Xbox.Services.141.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\Microsoft.Xbox.Services.141.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.142.GDK.C\Microsoft.Xbox.Services.142.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.142.GDK.C\Microsoft.Xbox.Services.142.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142\Microsoft.Xbox.Services.142.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C.Thunks\Microsoft.Xbox.Services.141.GDK.C.Thunks.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\Microsoft.Xbox.Services.141.GDK.C.Thunks.pdb
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C.Thunks\Microsoft.Xbox.Services.141.GDK.C.Thunks.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\Microsoft.Xbox.Services.141.GDK.C.Thunks.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C.Thunks\Microsoft.Xbox.Services.141.GDK.C.Thunks.dll %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\Microsoft.Xbox.Services.141.GDK.C.Thunks.dll.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.141.GDK.C\libHttpClient.141.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.141.GDK.C\libHttpClient.141.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\libHttpClient.141.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.142.GDK.C\libHttpClient.142.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.142.GDK.C\libHttpClient.142.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142\libHttpClient.142.GDK.C.lib.remove

set TYPE=debug
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C\Microsoft.Xbox.Services.141.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C\Microsoft.Xbox.Services.141.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\Microsoft.Xbox.Services.141.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.142.GDK.C\Microsoft.Xbox.Services.142.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.142.GDK.C\Microsoft.Xbox.Services.142.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142\Microsoft.Xbox.Services.142.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C.Thunks\Microsoft.Xbox.Services.141.GDK.C.Thunks.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\Microsoft.Xbox.Services.141.GDK.C.Thunks.pdb
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C.Thunks\Microsoft.Xbox.Services.141.GDK.C.Thunks.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\Microsoft.Xbox.Services.141.GDK.C.Thunks.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\Microsoft.Xbox.Services.141.GDK.C.Thunks\Microsoft.Xbox.Services.141.GDK.C.Thunks.dll %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\Microsoft.Xbox.Services.141.GDK.C.Thunks.dll.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.141.GDK.C\libHttpClient.141.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.141.GDK.C\libHttpClient.141.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v141\libHttpClient.141.GDK.C.lib.remove
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.142.GDK.C\libHttpClient.142.GDK.C.pdb %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142
copy %BUILD_BINARIESDIRECTORY%\%TYPE%\%PLAT%\libHttpClient.142.GDK.C\libHttpClient.142.GDK.C.lib %SDK_DROP_LOCATION_GDK_BIN%\binaries\%PLAT_LAYOUT_NAME%\%TYPE%\v142\libHttpClient.142.GDK.C.lib.remove

copy %BUILD_SOURCESDIRECTORY%\Source\Shared\build_version.h %SDK_DROP_LOCATION_GDK%

set BUILD_INFO_PATH=%SDK_DROP_LOCATION_GDK%\build_info.txt
set BUILD_INFO_BODY="%SDK_DROP_LOCATION%    https://microsoft.visualstudio.com/Xbox.Services/_build/index?buildId=%BUILD_BUILDID%&_a=summary"
del %BUILD_INFO_PATH%
echo %BUILD_INFO_BODY% > %BUILD_INFO_PATH%

REM ------------------- GDK DOCS BEGIN-------------------
set PATH_GDK_DOCS=%SDK_DROP_LOCATION%\GDK-Docs
set PATH_GDK_DOCS_DROP=%PATH_GDK_DOCS%\docs
mkdir %PATH_GDK_DOCS%
rmdir /s /q %PATH_GDK_DOCS%
mkdir %PATH_GDK_DOCS_DROP%
set BUILD_TOOLS=%BUILD_STAGINGDIRECTORY%\sdk.buildtools\buildMachine
call %BUILD_TOOLS%\Noggin\GenerateReferenceDocs.cmd %SDK_DROP_LOCATION%\include %PATH_GDK_DOCS_DROP%
copy %BUILD_TOOLS%\Noggin\CopyReferenceDocsToDocsRepo.cmd %PATH_GDK_DOCS%

REM -------------------DONE-------------------
:finalize

echo.
echo Done postBuildScript.cmd
echo.
endlocal

:done
exit /b
