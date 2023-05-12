@echo off
setlocal
pushd build
clang -g -c ../posix.c ../input_buffer.c ../statement.c -D _CRT_SECURE_NO_WARNINGS || exit /B
popd
clang -g -o build/adsql.exe adsql.c build\*.o -D _CRT_SECURE_NO_WARNINGS || exit /B
.\build\adsql.exe
endlocal
