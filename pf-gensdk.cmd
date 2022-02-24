set SCRIPT_PATH=%~dp0
set PF_ROOT=%SCRIPT_PATH%..\..\..

call %SCRIPT_PATH%\pf-backupandclean.cmd
pushd .
cd %PF_ROOT%\SDKGenerator\
call ts-node generate.js -destpath %PF_ROOT%\sdks\PlayFabCoreCSdk -apiSpecPath C:\git\pf\SDKGenerator\privateTemplates\PlayFabCoreCSdk_Template\CeruleanSwagger -buildIdentifier PlayFabCoreCSdk_manual
popd


