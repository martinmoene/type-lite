#include "nonstd/type.hpp"

type_DEFINE_TYPE( Ordered, ordered, int )

type_DEFINE_SUBTYPE_ND( Day , Ordered )
type_DEFINE_SUBTYPE_ND( Year, Ordered )

int main()
{
    // Note: undesired:
    bool result = Day(21) < Year(2019);

    return to_value( Day(21) );
}
// g++ -Wall -std=c++98 -I../include -o 04-sub 04-sub.cpp && 04-sub.exe
// cl -nologo -W3 -EHsc -I../include 04-sub.cpp && 04-sub.exe
// 04-sub.exe & echo %ERRORLEVEL%
