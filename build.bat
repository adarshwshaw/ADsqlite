@echo off
clang -g -o build/adsql.exe adsql.c posix.c -D _CRT_SECURE_NO_WARNINGS || exit /B
.\build\adsql.exe
