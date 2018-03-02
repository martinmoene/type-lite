#include "nonstd/type.hpp" 
#include <cmath> 
#include <iostream>

namespace strong {

type_DEFINE_TYPE( Integer, numeric, int )
type_DEFINE_FUNCTION( Integer, abs, std::abs )

}

int main()
{
	 std::cout << abs( strong::Integer(-7) ) << "\n";
}
// g++ -Wall -std=c++98 -I../include -o 05-function 05-function.cpp && 05-function.exe
// cl -nologo -W3 -EHsc -I../include/ 05-function.cpp && 05-function.exe
