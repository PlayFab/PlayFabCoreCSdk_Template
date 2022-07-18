@echo on

cd /d %BUILD_BINARIESDIRECTORY%
dir /s /b *.dll
del /s /q Microsoft.Win32.*.dll
del /s /q System.*.dll
