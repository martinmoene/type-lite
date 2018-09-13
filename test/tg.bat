@setlocal
@set std=%1
@if "%std%"=="" set std=c++11
g++ -std=%std% -O2 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wno-unused-parameter -I../include/nonstd -o type-main.t.exe type-main.t.cpp type.t.cpp && type-main.t.exe
@endlocal

