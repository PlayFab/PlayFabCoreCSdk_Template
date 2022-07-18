set 

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvars64.bat" %*

set

echo on
echo VCToolsInstallDir=%VCToolsInstallDir%

rem log compiler version used
"%VCToolsInstallDir%bin\Hostx64\x64\cl" -Bv
cmd /c "exit /b 0"
