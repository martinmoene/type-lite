@setlocal
@set std=%1
@if not "%std%"=="" set std=-std:%std%
set cppcorecheckinclude=%VCINSTALLDIR%/Auxiliary/VS/include
cl -W3 -EHsc %std% -I../include/nonstd -I"%cppcorecheckinclude%" type-main.t.cpp type.t.cpp && type-main.t.exe
@endlocal
