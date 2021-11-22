if "%BUILD_TOOLS%" EQU "" echo off && echo set BUILD_TOOLS to the path of vZip.  eg set BUILD_TOOLS=c:\git\sdk.buildtools\buildMachine
if "%BUILD_TOOLS%" EQU "" goto EOF

set SCRIPT_PATH=%~dp0
set PF_ROOT=%SCRIPT_PATH%..\..\..

set PFSDK_BACKUP_VER=%DATE:~10,4%-%DATE:~7,2%-%DATE:~4,2%.%TIME:~0,2%-%TIME:~3,2%-%TIME:~6,2%
%BUILD_TOOLS%\vZip.exe /FOLDER:%PF_ROOT%\sdks\XPlatCSdk /OUTPUTNAME:%PF_ROOT%\sdks\XPlatCSdk-%PFSDK_BACKUP_VER%.zip /EXCLUDE:external,.git,.vs,x64
rmdir /s /q %PF_ROOT%\sdks\XPlatCSdk\code
rmdir /s /q %PF_ROOT%\sdks\XPlatCSdk\test
rmdir /s /q %PF_ROOT%\sdks\XPlatCSdk\build