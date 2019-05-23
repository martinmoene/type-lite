#include "nonstd/type.hpp"
#include <iostream>

namespace strong {

type_DEFINE_TYPE( Integer, numeric, int )
type_DEFINE_TYPE( Scalar , numeric, double )

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, nonstd::type<T,Tag,D> const & v )
{
    return os << "[type:" << v.get() << "]";
}
}

int main()
{
	 std::cout <<
	    "\nInteger: " << strong::Integer( 42     ) <<
	    "\nScalar : " << strong::Scalar ( 3.1415 ) << "\n";
}
// g++ -Wall -std=c++98 -I../include -o 06-stream 06-stream.cpp && 06-stream.exe
// cl -nologo -W3 -EHsc -I../include 06-stream.cpp && 06-stream.exe
