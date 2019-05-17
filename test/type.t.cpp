// ToDo: noexcept(...)

// Copyright 2018-2019 by Martin Moene
//
// https://github.com/martinmoene/type
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "type-main.t.hpp"
#include <cstddef>
#include <cmath>
#include <cstdlib>
#include <vector>

#ifndef  type_CONFIG_CONFIRMS_COMPILATION_ERRORS
# define type_CONFIG_CONFIRMS_COMPILATION_ERRORS  0
#endif

namespace {

using namespace nonstd;

struct Tag;

CASE( "type: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    type< int, struct Tag, no_default_t > x;
#endif
}

CASE( "type: Allows to default-construct a type thus defined" )
{
    type< int, struct Tag > x;

    EXPECT( x.get() == 0 );
}

CASE( "type: Allows to construct a type from its underlying type" )
{
    type< char, struct Tag > x('y');

    EXPECT( x.get() == 'y' );
}

CASE( "boolean: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    nonstd::boolean< struct Tag, no_default_t > x;
#endif
}

CASE( "boolean: Allows to default-construct a type thus defined" )
{
    nonstd::boolean< struct Tag > x;

    EXPECT( x.get() == false );
}

CASE( "boolean: Allows to construct a type from its underlying type" )
{
    nonstd::boolean< struct Tag > x( true );

    EXPECT( x.get() == true );
}

CASE( "logical: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    logical< int, struct Tag, no_default_t > x;
#endif
}

CASE( "logical: Allows to default-construct a type thus defined" )
{
    logical< int, struct Tag > x;

    EXPECT( x.get() == 0 );
}

CASE( "logical: Allows to construct a type from its underlying type" )
{
    logical< int, struct Tag > x( 7 );

    EXPECT( x.get() == 7 );
}

CASE( "equality: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    equality< int, struct Tag, no_default_t > x;
#endif
}

CASE( "equality: Allows to default-construct a type thus defined" )
{
    equality< int, struct Tag > x;

    EXPECT( x.get() == 0 );
}

CASE( "equality: Allows to construct a type from its underlying type" )
{
    equality< int, struct Tag > x( 7 );

    EXPECT( x.get() == 7 );
}

CASE( "bits: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    bits< unsigned int, struct Tag, no_default_t > x;
#endif
}

CASE( "bits: Allows to default-construct a type thus defined" )
{
    bits< unsigned int, struct Tag > x;

    EXPECT( x.get() == 0 );
}

CASE( "bits: Allows to construct a type from its underlying type" )
{
    bits< unsigned int, struct Tag > x( 0x5a5a );

    EXPECT( x.get() == 0x5a5a );
}

CASE( "ordered: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    ordered< int, struct Tag, no_default_t > x;
#endif
}

CASE( "ordered: Allows to default-construct a type thus defined" )
{
    ordered< int, struct Tag > x;

    EXPECT( x.get() == 0 );
}

CASE( "ordered: Allows to construct a type from its underlying type" )
{
    ordered< int, struct Tag > x( 7 );

    EXPECT( x.get() == 7 );
}

CASE( "numeric: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    numeric< int, struct Tag, no_default_t > x;
#endif
}

CASE( "numeric: Allows to default-construct a type thus defined" )
{
    numeric< int, struct Tag > x;

    EXPECT( x.get() == 0 );
}

CASE( "numeric: Allows to construct a type from its underlying type" )
{
    numeric< int, struct Tag > x( 7 );

    EXPECT( x.get() == 7 );
}

CASE( "quantity: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    quantity< int, struct Tag, no_default_t > x;
#endif
}

CASE( "quantity: Allows to default-construct a type thus defined" )
{
    quantity< int, struct Tag > x;

    EXPECT( x.get() == 0 );
}

CASE( "quantity: Allows to construct a type from its underlying type" )
{
    quantity< int, struct Tag > x( 7 );

    EXPECT( x.get() == 7 );
}

CASE( "address: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    address< int *, std::ptrdiff_t, struct Tag, no_default_t > x;
#endif
}

CASE( "address: Allows to default-construct a type thus defined" )
{
    address< int *, std::ptrdiff_t, struct Tag > x;

#if type_CPP11_OR_GREATER
    EXPECT( x.get() == nullptr );
#else
    EXPECT( x.get() == NULL );
#endif
}

CASE( "address: Allows to construct a type from its underlying type" )
{
    int i;
    address< int *, std::ptrdiff_t, struct Tag > x( &i );

    EXPECT( x.get() == &i );
}

CASE( "offset: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    offset< int, struct Tag, no_default_t > x;
#endif
}

CASE( "offset: Allows to default-construct a type thus defined" )
{
    offset< int, struct Tag > x;

    EXPECT( x.get() == 0 );
}

CASE( "offset: Allows to construct a type from its underlying type" )
{
    offset< int, struct Tag > x( 7 );

    EXPECT( x.get() == 7 );
}


// -----------------------------------------------------------------------

type_DEFINE_TYPE( Num, numeric, int )
type_DEFINE_FUNCTION( Num, abs, std::abs )


CASE("type_DEFINE_FUNCTION")
{
    std::cout << "abs( Num(-7) ): " << abs( Num(-7) ) << "\n";
}

typedef bits< unsigned short, struct BitsTag > Bits;

typedef address< int *, std::ptrdiff_t, struct AddressTag > Address;
typedef Address::offset_type Offset;

type_constexpr14 void foo()
{
    Bits a(0x1), b(0x2);

    swap( a, b );
}

typedef nonstd::boolean< struct ExBoolTag  > ExplicitBool;
typedef nonstd::boolean< struct ExBoolTag2 > ExplicitBool2;

typedef numeric< int, struct Tag, no_default_t > Int;
typedef numeric< int, struct Tag               > DefInt;

type_DEFINE_FUNCTION( Int, abs, std::abs )

CASE("")
{

    Bits a(0x1), b(0x2);

    Bits c = a | b;

    Bits d = ~c;

    Bits::underlying_type ut(1);

    foo();

    Int i(-42);
    Int j(( type<int,struct Tag,no_default_t>( 3 ) ));
    Int k(( abs( j ) ));
    j = i;
//    Int j( abs( i ) );
//    Int j;
    swap( i, j );
    DefInt f;

//    std::vector<Int> vi(3);
    std::vector<DefInt> vdi(3);

    i++;
    bool _ = i != i;

    ExplicitBool  eb(true);
    ExplicitBool2 eb2(true);

    if ( eb ) {;}

    eb = ExplicitBool(false);

    eb = !eb;

//    int x = eb;

    bool result  = eb == eb;
    bool result2  = !(eb == eb);
//    bool result2 = eb == eb2;

    Address address( NULL );
    Offset  offset ( 7 );

    offset = offset;

    offset + offset;
    offset - offset;

    address - address;
    address + offset;
    address - offset;
    offset  + address;

//    address + address;
//    offset  - address;

#if type_HAVE_STD_HASH
//    std::size_t r = std::hash<DefInt>()( k );
#endif
}

} // anonymous namespace
