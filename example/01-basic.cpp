#include "nonstd/type.hpp"

#if 1
    type_DEFINE_TYPE_ND( Ordered, ordered, int )
    type_DEFINE_SUBTYPE_ND( Day , Ordered )
    type_DEFINE_SUBTYPE_ND( Year, Ordered )
#else
    typedef nonstd::ordered<int, struct day_tag , nonstd::no_default_t> Day;
    typedef nonstd::ordered<int, struct year_tag, nonstd::no_default_t> Year;
#endif

enum Month
{
    January=1, February, March, April, May, June,
    July, August, September, October, November, December
};

class Date
{
public:
    constexpr Date( Year year_, Month month_, Day day_)
    : year(year_), month(month_), day(day_) {}

    // ...

    Year  year;
    Month month;
    Day   day;
};

constexpr bool operator<( Date a, Date b )
{
    return a.year  < b.year
        || a.year == b.year && a.month  < b.month
        || a.year == b.year && a.month == b.month && a.day < b.day;
}

int main()
{
    auto date = Date( Year(2018), July, Day(21) );  // OK
//  date = Date( 2018, July, 21 );                  // compile-time error
//  date = Date( Day(21), July, Year(2018) );       // compile-time error
//  date = Date( July, Day(21), Year(2018) );       // compile-time error

    return Date( Year(2019), June, Day(28) )
         < Date( Year(2019), July, Day(24) );
}

// g++ -Wall -std=c++14 -I../include -o 01-basic 01-basic.cpp
// cl -nologo -W3 -EHsc -I../include 01-basic.cpp
