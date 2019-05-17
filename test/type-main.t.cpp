// Copyright 2018-2019 by Martin Moene
//
// https://github.com/martinmoene/type
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "type-main.t.hpp"

#define type_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define type_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "type version" "[.type][.version]" )
{
    type_PRESENT( type_MAJOR );
    type_PRESENT( type_MINOR );
    type_PRESENT( type_PATCH );
    type_PRESENT( type_VERSION );
}

CASE( "type configuration" "[.type][.config]" )
{
}

CASE( "C++ language: __cplusplus" "[.stdc++]" )
{
    type_PRESENT( __cplusplus );

#if _MSVC_LANG
    type_PRESENT( _MSVC_LANG );
#else
    type_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "C++ compiler: compiler version" "[.compiler]" )
{
    type_PRESENT( type_COMPILER_CLANG_VERSION );
    type_PRESENT( type_COMPILER_GNUC_VERSION );
    type_PRESENT( type_COMPILER_MSVC_VERSION );
}

CASE( "C++ language: presence of C++ language features" "[.stdlanguage]" )
{
    type_PRESENT( type_HAVE_CONSTEXPR_11 );
    type_PRESENT( type_HAVE_CONSTEXPR_14 );
    type_PRESENT( type_HAVE_EXPLICIT_CONVERSION );
    type_PRESENT( type_HAVE_IS_DELETE );
    type_PRESENT( type_HAVE_NOEXCEPT );
    type_PRESENT( type_HAVE_STD_HASH );
}

CASE( "C++ library: presence of C++ library features" "[.stdlibrary]" )
{
    type_PRESENT( type_HAS_CPP0X );

#if defined _HAS_CPP0X
    type_PRESENT( _HAS_CPP0X );
#else
    type_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++98 -I../include -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++03 -I../include -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++0x -I../include -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++11 -I../include -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++14 -I../include -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++17 -I../include -o type.t.exe type.t.cpp && type.t.exe --pass

cl -EHsc -I../include type.t.cpp && type.t.exe --pass
#endif

// end of file
