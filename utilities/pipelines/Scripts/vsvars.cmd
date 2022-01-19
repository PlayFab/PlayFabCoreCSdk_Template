set 

cd /d "C:\Program Files (x86)\Microsoft Visual Studio\2017\"
dir cl*.exe /s /b
dir vc*.bat /s /b

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\vsdevcmd\ext\vcvars.bat" x64
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsamd64_x86.bat"

set
