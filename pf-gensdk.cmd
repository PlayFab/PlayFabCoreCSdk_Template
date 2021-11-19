set SCRIPT_PATH=%~dp0
set PF_ROOT=%SCRIPT_PATH%..\..\..

call %SCRIPT_PATH%\pf-backupandclean.cmd
pushd .
cd %PF_ROOT%\SDKGenerator\
call ts-node generate.js -destpath %PF_ROOT%\sdks\XPlatCSdk -apiSpecGitUrl -buildIdentifier XPlatCSdk_manual
popd