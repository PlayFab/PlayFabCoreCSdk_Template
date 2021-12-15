@echo off
echo ========= Copying non-templated files from generated SDK back to template repository =========

set SCRIPT_PATH=%~dp0
set PF_ROOT=%SCRIPT_PATH%..\..\..
set PF_TEMPLATE=%SCRIPT_PATH%source\

set GENSDK=%PF_ROOT%\sdks\PlayFabCoreCSdk\

xcopy %GENSDK% %PF_TEMPLATE% /u /s /e /y
