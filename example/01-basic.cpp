#include "nonstd/type.hpp"

#if 1
    type_DEFINE_TYPE( Integer, numeric, int )
    type_DEFINE_SUBTYPE( Day , Integer )
    type_DEFINE_SUBTYPE( Year, Integer )
#else
    typedef nonstd::numeric<int, struct day_tag , nonstd::no_default_t> Day;
    typedef nonstd::numeric<int, struct year_tag, nonstd::no_default_t> Year;
#endif

enum Month
{
    January=1, February, March, April, May, June,
    July, August, September, October, November, December
};

class Date
{
public:
   Date( Year year, Month month, Day day ) {}
   // ...
};

int main()
{
    auto date = Date( Year(2018), July, Day(21) );  // OK
//  date = Date( 2018, July, 21 );                  // compile-time error
//  date = Date( Day(21), July, Year(2018) );       // compile-time error
//  date = Date( July, Day(21), Year(2018) );       // compile-time error
}

// g++ -Wall -std=c++11 -I../include -o 01-basic 01-basic.cpp
// cl -nologo -W3 -EHsc -I../include 01-basic.cpp
