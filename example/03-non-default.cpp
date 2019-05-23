#include "nonstd/type.hpp"

type_DEFINE_TYPE_ND( Day, ordered, int )

int main()
{
//  strong::Day day;  // nope

    return to_value( Day(21) );
}
// g++ -Wall -std=c++98 -I../include -o 03-non-default 03-non-default.cpp && 03-non-default.exe
// cl -nologo -W3 -EHsc -I../include 03-non-default.cpp && 03-non-default.exe
// 03-non-default.exe & echo %ERRORLEVEL%
