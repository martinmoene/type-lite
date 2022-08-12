#include "nonstd/type.hpp"
#include <limits>

typedef nonstd::equality<size_t, struct IndexTag,
    nonstd::custom_default_t<size_t, std::numeric_limits<size_t>::max()> > Index;

int main()
{
    Index i( 0 );
    return i != Index() ? 0 : 1;
}
// g++ -Wall -std=c++98 -I../include -o 02a-custom-default 02a-custom-default.cpp && 02a-custom-default.exe
// cl -nologo -W3 -EHsc -I../include 02a-custom-default.cpp && 02a-custom-default.exe
// 02a-custom-default.exe & echo %ERRORLEVEL%
