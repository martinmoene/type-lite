// ToDo: noexcept(...)

// Copyright 2018 by Martin Moene
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

namespace {

using namespace nonstd;

CASE( "type: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" ){}
CASE( "type: Allows to default-construct a type thus defined" ){}
CASE( "type: Allows to construct a type from its underlying type" ){}

CASE( "boolean: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" ){}
CASE( "boolean: Allows to default-construct a type thus defined" ){}
CASE( "boolean: Allows to construct a type from its underlying type" ){}

CASE( "logical: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" ){}
CASE( "logical: Allows to default-construct a type thus defined" ){}
CASE( "logical: Allows to construct a type from its underlying type" ){}

CASE( "equality: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" ){}
CASE( "equality: Allows to default-construct a type thus defined" ){}
CASE( "equality: Allows to construct a type from its underlying type" ){}

CASE( "bits: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" ){}
CASE( "bits: Allows to default-construct a type thus defined" ){}
CASE( "bits: Allows to construct a type from its underlying type" ){}

CASE( "ordered: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" ){}
CASE( "ordered: Allows to default-construct a type thus defined" ){}
CASE( "ordered: Allows to construct a type from its underlying type" ){}

CASE( "numeric: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" ){}
CASE( "numeric: Allows to default-construct a type thus defined" ){}
CASE( "numeric: Allows to construct a type from its underlying type" ){}

CASE( "quantity: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" ){}
CASE( "quantity: Allows to default-construct a type thus defined" ){}
CASE( "quantity: Allows to construct a type from its underlying type" ){}

CASE( "address: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" ){}
CASE( "address: Allows to default-construct a type thus defined" ){}
CASE( "address: Allows to construct a type from its underlying type" ){}

CASE( "offset: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" ){}
CASE( "offset: Allows to default-construct a type thus defined" ){}
CASE( "offset: Allows to construct a type from its underlying type" ){}


type_DEFINE_TYPE( Num, numeric, int )
type_DEFINE_FUNCTION( Num, abs, std::abs )


CASE("type_DEFINE_FUNCTION")
{
    std::cout << "abs( Num(-7) ): " << abs( Num(-7) ) << "\n";
}

struct ExBoolTag;
struct ExBoolTag2;
struct IntTag;
struct AddressTag;

typedef bits< unsigned short, struct BitsTag > Bits;

typedef address< int *, std::ptrdiff_t, struct AddressTag > Address;
typedef Address::offset_type Offset;

type_constexpr14 void foo()
{
    Bits a(0x1), b(0x2);

    swap( a, b );
}

typedef numeric< int, struct IntTag, no_default_t > Int;
typedef numeric< int, struct IntTag               > DefInt;

type_DEFINE_FUNCTION( Int, abs, std::abs )

CASE("")
{

    Bits a(0x1), b(0x2);

    Bits c = a | b;

    Bits::underlying_type ut(1);

    foo();

    Int i(-42);
    Int j(( type<int,IntTag,no_default_t>( 3 ) ));
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

    typedef nonstd::boolean< struct ExBoolTag  > ExplicitBool;
    typedef nonstd::boolean< struct ExBoolTag2 > ExplicitBool2;

    ExplicitBool  eb(true);
    ExplicitBool2 eb2(true);

    if ( eb ) {;}

    eb = ExplicitBool(false);

//    int x = eb;

    bool result  = eb == eb;
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
