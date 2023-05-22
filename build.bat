@echo off
setlocal
pushd build
clang -std=c11 -g -c ../posix.c ../input_buffer.c ../statement.c ../dbf.c -D _CRT_SECURE_NO_WARNINGS || exit /B
popd
clang -std=c11 -g -o build/adsql.exe adsql.c build\*.o -D _CRT_SECURE_NO_WARNINGS || exit /B
@REM .\build\adsql.exe
endlocal
