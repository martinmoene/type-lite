#include "nonstd/type.hpp"

type_DEFINE_TYPE( Integer, numeric, int )

int main()
{
    return to_value( Integer(7) + Integer() );
}
// g++ -Wall -std=c++98 -I../include -o 02-default 02-default.cpp && 02-default.exe
// cl -nologo -W3 -EHsc -I../include 02-default.cpp && 02-default.exe
// 02-default.exe & echo %ERRORLEVEL%
