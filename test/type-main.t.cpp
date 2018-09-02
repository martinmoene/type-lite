// Copyright 2018 by Martin Moene
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

CASE( "type version" "[.version]" )
{
    type_PRESENT( type_MAJOR );
    type_PRESENT( type_MINOR );
    type_PRESENT( type_PATCH );
    type_PRESENT( type_VERSION );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    type_PRESENT( __cplusplus );

#if _MSVC_LANG
    type_PRESENT( _MSVC_LANG );
#else
    type_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "type configuration" "[.config]" )
{
}

#if !type_HAVE_STD_OPTIONAL

CASE( "compiler version" "[.compiler]" )
{
#if type_COMPILER_GNUC_VERSION
    type_PRESENT( type_COMPILER_GNUC_VERSION );
#else
    type_ABSENT(  type_COMPILER_GNUC_VERSION );
#endif

#if type_COMPILER_MSVC_VERSION
    type_PRESENT( type_COMPILER_MSVC_VERSION );
#else
    type_ABSENT(  type_COMPILER_MSVC_VERSION );
#endif
}

CASE( "presence of C++ language features" "[.stdlanguage]" )
{
#if type_HAVE_AUTO
    type_PRESENT( type_HAVE_AUTO );
#else
    type_ABSENT(  type_HAVE_AUTO );
#endif

#if type_HAVE_NULLPTR
    type_PRESENT( type_HAVE_NULLPTR );
#else
    type_ABSENT(  type_HAVE_NULLPTR );
#endif

#if type_HAVE_STATIC_ASSERT
    type_PRESENT( type_HAVE_STATIC_ASSERT );
#else
    type_ABSENT(  type_HAVE_STATIC_ASSERT );
#endif

#if type_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG
    type_PRESENT( type_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#else
    type_ABSENT(  type_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#endif

#if type_HAVE_ALIAS_TEMPLATE
    type_PRESENT( type_HAVE_ALIAS_TEMPLATE );
#else
    type_ABSENT(  type_HAVE_ALIAS_TEMPLATE );
#endif

#if type_HAVE_CONSTEXPR_11
    type_PRESENT( type_HAVE_CONSTEXPR_11 );
#else
    type_ABSENT(  type_HAVE_CONSTEXPR_11 );
#endif

#if type_HAVE_CONSTEXPR_14
    type_PRESENT( type_HAVE_CONSTEXPR_14 );
#else
    type_ABSENT(  type_HAVE_CONSTEXPR_14 );
#endif

#if type_HAVE_ENUM_CLASS
    type_PRESENT( type_HAVE_ENUM_CLASS );
#else
    type_ABSENT(  type_HAVE_ENUM_CLASS );
#endif

#if type_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    type_PRESENT( type_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#else
    type_ABSENT(  type_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#endif

#if type_HAVE_EXPLICIT_CONVERSION
    type_PRESENT( type_HAVE_EXPLICIT_CONVERSION );
#else
    type_ABSENT(  type_HAVE_EXPLICIT_CONVERSION );
#endif

#if type_HAVE_INITIALIZER_LIST
    type_PRESENT( type_HAVE_INITIALIZER_LIST );
#else
    type_ABSENT(  type_HAVE_INITIALIZER_LIST );
#endif

#if type_HAVE_IS_DEFAULT
    type_PRESENT( type_HAVE_IS_DEFAULT );
#else
    type_ABSENT(  type_HAVE_IS_DEFAULT );
#endif

#if type_HAVE_IS_DELETE
    type_PRESENT( type_HAVE_IS_DELETE );
#else
    type_ABSENT(  type_HAVE_IS_DELETE );
#endif

#if type_HAVE_NOEXCEPT
    type_PRESENT( type_HAVE_NOEXCEPT );
#else
    type_ABSENT(  type_HAVE_NOEXCEPT );
#endif

#if type_HAVE_REF_QUALIFIER
    type_PRESENT( type_HAVE_REF_QUALIFIER );
#else
    type_ABSENT(  type_HAVE_REF_QUALIFIER );
#endif

#if type_HAVE_UNICODE_LITERALS
    type_PRESENT( type_HAVE_UNICODE_LITERALS );
#else
    type_ABSENT(  type_HAVE_UNICODE_LITERALS );
#endif
}

CASE( "presence of C++ library features" "[.stdlibrary]" )
{
#if type_HAVE_ARRAY
    type_PRESENT( type_HAVE_ARRAY );
#else
    type_ABSENT(  type_HAVE_ARRAY );
#endif

#if type_HAVE_CONDITIONAL
    type_PRESENT( type_HAVE_CONDITIONAL );
#else
    type_ABSENT(  type_HAVE_CONDITIONAL );
#endif

#if type_HAVE_CONTAINER_DATA_METHOD
    type_PRESENT( type_HAVE_CONTAINER_DATA_METHOD );
#else
    type_ABSENT(  type_HAVE_CONTAINER_DATA_METHOD );
#endif

#if type_HAVE_REMOVE_CV
    type_PRESENT( type_HAVE_REMOVE_CV );
#else
    type_ABSENT(  type_HAVE_REMOVE_CV );
#endif

#if type_HAVE_SIZED_TYPES
    type_PRESENT( type_HAVE_SIZED_TYPES );
#else
    type_ABSENT(  type_HAVE_SIZED_TYPES );
#endif

#if type_HAVE_TYPE_TRAITS
    type_PRESENT( type_HAVE_TYPE_TRAITS );
#else
    type_ABSENT(  type_HAVE_TYPE_TRAITS );
#endif

#if type_HAVE_WCHAR16_T
    type_PRESENT( type_HAVE_WCHAR16_T );
#else
    type_ABSENT(  type_HAVE_WCHAR16_T );
#endif

#if type_HAVE_WCHAR32_T
    type_PRESENT( type_HAVE_WCHAR32_T );
#else
    type_ABSENT(  type_HAVE_WCHAR32_T );
#endif

#if _HAS_CPP0X
    type_PRESENT( _HAS_CPP0X );
#else
    type_ABSENT(  _HAS_CPP0X );
#endif
}

#endif // type_HAVE_STD_OPTIONAL

CASE( "Configuration of type" "[.config]" )
{
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include/nonstd -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++98 -I../include/nonstd -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++03 -I../include/nonstd -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++0x -I../include/nonstd -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++11 -I../include/nonstd -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++14 -I../include/nonstd -o type.t.exe type.t.cpp && type.t.exe --pass
g++ -std=c++17 -I../include/nonstd -o type.t.exe type.t.cpp && type.t.exe --pass

cl -EHsc -I../include/nonstd type.t.cpp && type.t.exe --pass
#endif

// end of file
