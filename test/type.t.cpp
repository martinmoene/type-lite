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

struct CopyMove
{
    int v;
    explicit CopyMove(int v_ = 0) : v(v_) {}
    CopyMove( CopyMove const & other ) : v(other.v) {}
    CopyMove & operator=(CopyMove const & other ) { v = other.v; return *this; }

#if type_CPP11_OR_GREATER
    CopyMove( CopyMove && ) = default;
    CopyMove & operator=(CopyMove && ) = default;
#endif
};

type_constexpr bool operator==( CopyMove const & a, CopyMove const & b )
{
    return a.v == b.v;
}

type_constexpr bool operator<( CopyMove const & a, CopyMove const & b )
{
    return a.v < b.v;
}

std::ostream & operator<<( std::ostream & os, CopyMove const & x )
{
    return os << "[CopyMove:" << x.v << "]";
}

void swap( CopyMove & a, CopyMove & b )
{
    using std::swap;
    swap( a.v, b.v );
}

struct MoveOnly
{
    int v;
    explicit MoveOnly(int v_) : v(v_) {}

#if type_CPP11_OR_GREATER
    MoveOnly( MoveOnly const & ) = delete;
    MoveOnly & operator=(MoveOnly const & ) = delete;

    MoveOnly( MoveOnly && ) /*noexcept*/ = default;
    MoveOnly & operator=( MoveOnly && ) /*noexcept*/ = default;
#endif
};

type_constexpr bool operator==( MoveOnly const & a, MoveOnly const & b )
{
    return a.v == b.v;
}

std::ostream & operator<<( std::ostream & os, MoveOnly const & x )
{
    return os << "[MoveOnly:" << x.v << "]";
}

#define STATIC_ASSERT( expr ) \
    static_assert( expr, #expr )

CASE( "CopyMove: copyable and movable [.]" )
{
#if type_CPP11_OR_GREATER
    STATIC_ASSERT( std::is_copy_constructible<CopyMove>::value );
    STATIC_ASSERT( std::is_move_constructible<CopyMove>::value );
    STATIC_ASSERT( std::is_copy_assignable<   CopyMove>::value );
    STATIC_ASSERT( std::is_move_assignable<   CopyMove>::value );
#endif
}

CASE( "MoveOnly: movable only [.]" )
{
#if type_CPP11_OR_GREATER
    STATIC_ASSERT( !std::is_copy_constructible<MoveOnly>::value );
    STATIC_ASSERT( !std::is_copy_constructible<MoveOnly>::value );
    STATIC_ASSERT(  std::is_move_constructible<MoveOnly>::value );
    STATIC_ASSERT(  std::is_move_assignable<   MoveOnly>::value );
#endif
}

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, type<T,Tag,D> const & v )
{
    return os << "[type:" << v.get() << "]";
}

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, bits<T,Tag,D> const & v )
{
    return os << "[bits: 0x" << std::hex << v.get() << "]";
}

template< typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, ::nonstd::boolean<Tag,D> const & v )
{
    return os << "[boolean:" << (v ? true : false) << "]";
}

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, logical<T,Tag,D> const & v )
{
    return os << "[logical:" << v.get() << "]";
}

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, equality<T,Tag,D> const & v )
{
    return os << "[equality:" << v.get() << "]";
}

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, ordered<T,Tag,D> const & v )
{
    return os << "[ordered:" << v.get() << "]";
}

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, numeric<T,Tag,D> const & v )
{
    return os << "[numeric:" << v.get() << "]";
}

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, nonstd::quantity<T,Tag,D> const & v )
{
    return os << "[quantity:" << v.get() << "]";
}

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, offset<T,Tag,D> const & v )
{
    return os << "[offset:" << v.get() << "]";
}

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, address<T,Tag,D> const & v )
{
    return os << "[address:" << v.get() << "]";
}

// -----------------------------------------------------------------------
// type:

typedef type< int     , struct Tag > IntType;
typedef type< CopyMove, struct Tag > CopyMoveType;
typedef type< MoveOnly, struct Tag > MoveOnlyType;

CASE( "type: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    type< int, struct Tag, no_default_t > x;
#endif
    EXPECT( true );
}

CASE( "type: Allows to default-construct a type thus defined" )
{
    CopyMoveType x;

    EXPECT( to_value( x ) == CopyMove() );
}

CASE( "type: Allows to custom-default-construct a type thus defined" )
{
    typedef type< int, struct Tag, custom_default_t< int, 5 > > CustomDefaultType;
    CustomDefaultType x;

    EXPECT( to_value( x ) == 5 );
}

CASE( "type: Allows to copy-construct a type from its underlying type" )
{
    CopyMoveType x( CopyMove(7) );

    EXPECT( to_value( x ) == CopyMove(7) );
}

CASE( "type: Allows to move-construct a type from its underlying type (C++11)" )
{
#if type_CPP11_OR_GREATER
    MoveOnlyType x( MoveOnly{42} );

    EXPECT( to_value( x ) == MoveOnly{42} );
#else
    EXPECT( !!"type: move-construction is not available (no C++11)" );
#endif
}

CASE( "type: Allows to copy-construct a type" )
{
    CopyMoveType x( CopyMove(7) );

    CopyMoveType y( x );

    EXPECT( to_value( y ) == CopyMove(7) );
}

CASE( "type: Allows to move-construct a type (C++11)" )
{
#if type_CPP11_OR_GREATER
    MoveOnlyType x( MoveOnlyType( MoveOnly{42} ) );

    EXPECT( to_value( x ) == MoveOnly{42} );
#else
    EXPECT( !!"type: move-construction is not available (no C++11)" );
#endif
}

CASE( "type: Allows to copy-assign a type" )
{
    CopyMoveType x;
    CopyMoveType y( CopyMove(7) );

    x = y;

    EXPECT( to_value( x ) == CopyMove(7) );
}

CASE( "type: Allows to move-assign a type (C++11)" )
{
#if type_CPP11_OR_GREATER
    MoveOnlyType x( MoveOnly{0} );

    x = MoveOnlyType( MoveOnly{42} );

    EXPECT( to_value( x ) == MoveOnly{42} );
#else
    EXPECT( !!"type: move-assignment is not available (no C++11)" );
#endif
}

CASE( "type: Allows to copy-swap a type" )
{
    CopyMoveType x( CopyMove(3) );
    CopyMoveType y( CopyMove(7) );

    swap( x, y );

    EXPECT( to_value( x ) == CopyMove(7) );
    EXPECT( to_value( y ) == CopyMove(3) );
}

CASE( "type: Allows to move-swap a type (C++11)" )
{
#if type_CPP11_OR_GREATER
    MoveOnlyType x( MoveOnly{3} );
    MoveOnlyType y( MoveOnly{7} );

    swap( x, y );

    EXPECT( to_value( x ) == MoveOnly{7} );
    EXPECT( to_value( y ) == MoveOnly{3} );
#else
    EXPECT( !!"type: move-assignment is not available (no C++11)" );
#endif
}

CASE( "type: Allows to obtain hash of a type object (C++11)" )
{
#if type_CPP11_OR_GREATER
    EXPECT( make_hash( IntType(7) ) != make_hash( IntType(9) ));
#else
    EXPECT( !!"type: std::hash is not available (no C++11)" );
#endif
}

// -----------------------------------------------------------------------
// boolean:

typedef nonstd::boolean< struct Tag > Boolean;
typedef nonstd::boolean< struct TagA> BooleanA;
typedef nonstd::boolean< struct TagB> BooleanB;

CASE( "boolean: Disallows to default-construct a boolean thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    nonstd::boolean< struct Tag, no_default_t > x;
#endif
    EXPECT( true );
}

CASE( "boolean: Disallows to substitute booleans with different tags (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    BooleanA a(true);
    a = BooleanB(false);
#endif
    EXPECT( true );
}

CASE( "boolean: Allows to default-construct a boolean thus defined" )
{
    Boolean x;

    EXPECT( to_value( x ) == false );
}

CASE( "boolean: Allows to custom-default-construct a boolean thus defined" )
{
    typedef nonstd::boolean< struct Tag, custom_default_t< bool, true > > CustomDefaultType;
    CustomDefaultType x;

    EXPECT( to_value( x ) == true );
}

CASE( "boolean: Allows to copy-construct a boolean from its underlying type" )
{
    Boolean x( true );

    EXPECT( to_value( x ) == true );
}

CASE( "boolean: Allows explicit conversion to a native bool" )
{
    Boolean x( false );
    Boolean y( true  );

    EXPECT_NOT( x );
    EXPECT(     y );
}

CASE( "boolean: Allows to negate a boolean" )
{
    Boolean x( false );

    EXPECT( !x );
}

CASE( "boolean: Allows to compare a boolean for equality" )
{
    Boolean x( false );
    Boolean y( true  );

    EXPECT(     x == x );
    EXPECT_NOT( x == y );

    EXPECT_NOT( x != x );
    EXPECT(     x != y );
}

CASE( "boolean: Allows to obtain hash of a boolean object (C++11)" )
{
#if type_CPP11_OR_GREATER
    EXPECT( make_hash( Boolean(false) ) != make_hash( Boolean(true) ));
#else
    EXPECT( !!"type: std::hash is not available (no C++11)" );
#endif
}

// -----------------------------------------------------------------------
// logical:

typedef logical< CopyMove, struct Tag > CopyMoveLogical;
typedef logical< MoveOnly, struct Tag > MoveOnlyLogical;
typedef logical< bool    , struct Tag > BoolLogical;


CASE( "logical: Disallows to default-construct a logical thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    logical< int, struct Tag, no_default_t > x;
#endif
    EXPECT( true );
}

CASE( "logical: Allows to default-construct a logical thus defined" )
{
    CopyMoveLogical x;

    EXPECT( to_value( x ) == CopyMove(0) );
}

CASE( "logical: Allows to custom-default-construct a logical thus defined" )
{
    typedef logical< int, struct Tag, custom_default_t< int, 5 > > CustomDefaultLogical;
    CustomDefaultLogical x;

    EXPECT( to_value( x ) == 5 );
}

CASE( "logical: Allows to copy-construct a logical from its underlying type" )
{
    CopyMoveLogical x( CopyMove(7) );

    EXPECT( to_value( x ) == CopyMove(7) );
}

CASE( "logical: Allows to move-construct a logical from its underlying type (C++11)" )
{
#if type_CPP11_OR_GREATER
    MoveOnlyLogical x( MoveOnly{42} );

    EXPECT( to_value( x ).v == 42 );
#else
    EXPECT( !!"logical: move-construction is not available (no C++11)" );
#endif
}

CASE( "logical: Allows to negate a logical" )
{
    BoolLogical x( true );
    BoolLogical y( false  );

    EXPECT_NOT( to_value( ! x ) );
    EXPECT(     to_value( ! y ) );
}

CASE( "logical: Allows to and two logicals" )
{
    BoolLogical x( true );
    BoolLogical y( false  );

    EXPECT(     to_value( x && x ) );
    EXPECT_NOT( to_value( y && y ) );
    EXPECT_NOT( to_value( x && y ) );
}

CASE( "logical: Allows to or two logicals" )
{
    BoolLogical x( true );
    BoolLogical y( false  );

    EXPECT(     to_value( x || x ) );
    EXPECT(     to_value( x || y ) );
    EXPECT_NOT( to_value( y || y ) );
}

CASE( "logical: Allows to obtain hash of a logical object (C++11)" )
{
#if type_CPP11_OR_GREATER
    EXPECT( make_hash( BoolLogical(false) ) != make_hash( BoolLogical(true) ) );
#else
    EXPECT( !!"type: std::hash is not available (no C++11)" );
#endif
}

// -----------------------------------------------------------------------
// equality:

typedef equality< int     , struct Tag > IntEquality;
typedef equality< CopyMove, struct Tag > CopyMoveEquality;
typedef equality< MoveOnly, struct Tag > MoveOnlyEquality;

CASE( "equality: Disallows to default-construct an equality thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    equality< int, struct Tag, no_default_t > x;
#endif
    EXPECT( true );
}

CASE( "equality: Allows to default-construct an equality thus defined" )
{
    CopyMoveEquality x;

    EXPECT( to_value( x ) == CopyMove(0) );
}

CASE( "equality: Allows to custom-default-construct a equality thus defined" )
{
    typedef equality< int, struct Tag, custom_default_t< int, 5 > > CustomDefaultEquality;
    CustomDefaultEquality x;

    EXPECT( to_value( x ) == 5 );
}

CASE( "equality: Allows to copy-construct an equality from its underlying type" )
{
    CopyMoveEquality x( CopyMove(7) );

    EXPECT( to_value( x ) == CopyMove(7) );
}

CASE( "equality: Allows to move-construct an equality from its underlying type (C++11)" )
{
#if type_CPP11_OR_GREATER
    MoveOnlyEquality x( MoveOnly{42} );

    EXPECT( to_value( x ).v == 42 );
#else
    EXPECT( !!"equality: move-construction is not available (no C++11)" );
#endif
}

CASE( "equality: Allows to compare an equality for equality" )
{
    CopyMoveEquality x( CopyMove( 7)  );
    CopyMoveEquality y( CopyMove(42) );

    EXPECT(     x == x );
    EXPECT_NOT( x == y );

    EXPECT_NOT( x != x );
    EXPECT(     x != y );
}

CASE( "equality: Allows to obtain hash of an equality object (C++11)" )
{
#if type_CPP11_OR_GREATER
    EXPECT( make_hash( IntEquality(7) ) != make_hash( IntEquality(9) ) );
#else
    EXPECT( !!"type: std::hash is not available (no C++11)" );
#endif
}

// -----------------------------------------------------------------------
// bits:

typedef bits< CopyMove, struct Tag > CopyMoveBits;
typedef bits< MoveOnly, struct Tag > MoveOnlyBits;
typedef bits< unsigned int, struct Tag > Bits;

CASE( "bits: Disallows to default-construct a bits thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    bits< unsigned int, struct Tag, no_default_t > x;
#endif
    EXPECT( true );
}

CASE( "bits: Allows to default-construct a bits thus defined" )
{
    bits< unsigned int, struct Tag > x;

    EXPECT( to_value( x ) == 0u );
}

CASE( "bits: Allows to custom-default-construct a bits thus defined" )
{
    typedef bits< unsigned int, struct Tag, custom_default_t< unsigned int, 5 > > CustomDefaultBits;
    CustomDefaultBits x;

    EXPECT( to_value( x ) == 5 );
}

CASE( "bits: Allows to copy-construct a bits from its underlying type" )
{
    CopyMoveBits x( CopyMove(0x5a5a) );

    EXPECT( to_value( x ) == CopyMove(0x5a5a) );
}

CASE( "bits: Allows to move-construct a bits from its underlying type (C++11)" )
{
#if type_CPP11_OR_GREATER
    bits< MoveOnly, struct Tag > x( MoveOnly{42} );

    EXPECT( to_value( x ).v == 42 );
#else
    EXPECT( !!"bits: move-construction is not available (no C++11)" );
#endif
}

CASE( "bits: Allows to compare bits for equality" )
{
    Bits x( 0x5a5a );
    Bits y( 0xa5a5 );

    EXPECT(     x == x );
    EXPECT_NOT( x == y );

    EXPECT_NOT( x != x );
    EXPECT(     x != y );
}

CASE( "bits: Allows to negate bits" )
{
    Bits x( static_cast<unsigned int>( ~0 ) );
    Bits y(  0 );

    EXPECT( ~x == y );
}

CASE( "bits: Allows to and bits" )
{
    SETUP("") {
        Bits z;
        Bits x( 0x5a5a );
        Bits y( 0xa5a5 );

        EXPECT( (x & x) == x );
        EXPECT( (x & y) == z );
    }
}

CASE( "bits: Allows to or bits" )
{
    SETUP("") {
        Bits x( 0x5a5a );
        Bits y( 0xa5a5 );
        Bits r( to_value( x ) | to_value( y ) );

        EXPECT( (x | x) == x );
        EXPECT( (x | y) == r );
    }
}

CASE( "bits: Allows to xor bits" )
{
    SETUP("") {
        Bits z;
        Bits x( 0x5a5a );
        Bits y( 0xa5a5 );
        Bits r( to_value( x ) ^ to_value( y ) );

        EXPECT( (x ^ x) == z );
        EXPECT( (x ^ y) == r );
    }
}

CASE( "bits: Allows to shift-left bits" )
{
    SETUP("") {
        Bits x( 0x5a5a );
        Bits y( x );
        Bits r( to_value( x ) << 3 );

    SECTION("") {
        EXPECT( (x << 0) == x );
        EXPECT( (x << 3) == r );
    }
    SECTION("") {
        EXPECT( (x <<= 0) == y );
    }
    SECTION("") {
        EXPECT( (x <<= 3) == r );
    }}
}

CASE( "bits: Allows to shift-right bits" )
{
    SETUP("") {
        Bits x( 0x5a5a );
        Bits y( x );
        Bits r( to_value( x ) >> 3 );

    SECTION("") {
        EXPECT( (x >> 0) == x );
        EXPECT( (x >> 3) == r );
    }
    SECTION("") {
        EXPECT( (x >>= 0) == y );
    }
    SECTION("") {
        EXPECT( (x >>= 3) == r );
    }}
}

CASE( "bits: Allows to obtain hash of a bits object (C++11)" )
{
#if type_CPP11_OR_GREATER
    EXPECT( make_hash( Bits(7) ) != make_hash( Bits(9) ) );
#else
    EXPECT( !!"type: std::hash is not available (no C++11)" );
#endif
}

// -----------------------------------------------------------------------
// ordered:

typedef ordered< int, struct Tag > Ordered;
typedef ordered< CopyMove, struct Tag > CopyMoveOrdered;
typedef ordered< MoveOnly, struct Tag > MoveOnlyOrdered;

CASE( "ordered: Disallows to default-construct an ordered thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    ordered< int, struct Tag, no_default_t > x;
#endif
    EXPECT( true );
}

CASE( "ordered: Allows to default-construct an ordered thus defined" )
{
    Ordered x;

    EXPECT( to_value( x ) == 0 );
}

CASE( "ordered: Allows to custom-default-construct an ordered thus defined" )
{
    typedef ordered< int, struct Tag, custom_default_t< int, 5 > > CustomDefaultOrdered;
    CustomDefaultOrdered x;

    EXPECT( to_value( x ) == 5 );
}

CASE( "ordered: Allows to copy-construct an ordered from its underlying type" )
{
    CopyMoveOrdered x( CopyMove(7) );

    EXPECT( to_value( x ) == CopyMove(7) );
}

CASE( "ordered: Allows to move-construct an ordered from its underlying type (C++11)" )
{
#if type_CPP11_OR_GREATER
    MoveOnlyOrdered x( MoveOnly{42} );

    EXPECT( to_value( x ).v == 42 );
#else
    EXPECT( !!"ordered: move-construction is not available (no C++11)" );
#endif
}

CASE( "ordered: Allows to compare an ordered for equality" )
{
    CopyMoveOrdered x( CopyMove( 7) );
    CopyMoveOrdered y( CopyMove(42) );

    EXPECT(     x == x );
    EXPECT_NOT( x == y );

    EXPECT_NOT( x != x );
    EXPECT(     x != y );
}

CASE( "ordered: Allows to compare an ordered for order" )
{
    CopyMoveOrdered x( CopyMove( 7) );
    CopyMoveOrdered y( CopyMove(42) );

    EXPECT( x <  y );
    EXPECT( x <= x );
    EXPECT( y >  x );
    EXPECT( y >= y );

    EXPECT_NOT( y <  x );
    EXPECT_NOT( y <= x );
    EXPECT_NOT( x >  y );
    EXPECT_NOT( x >= y );
}

CASE( "ordered: Allows to obtain hash of an ordered object (C++11)" )
{
#if type_CPP11_OR_GREATER
    EXPECT( make_hash( Ordered(7) ) != make_hash( Ordered(9) ) );
#else
    EXPECT( !!"type: std::hash is not available (no C++11)" );
#endif
}

// -----------------------------------------------------------------------
// numeric:

typedef numeric< int, struct Tag > Numeric;
typedef numeric< CopyMove, struct Tag > CopyMoveNumeric;
typedef numeric< MoveOnly, struct Tag > MoveOnlyNumeric;

CASE( "numeric: Disallows to default-construct a numeric thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    numeric< int, struct Tag, no_default_t > x;
#endif
    EXPECT( true );
}

CASE( "numeric: Allows to default-construct a numeric thus defined" )
{
    Numeric x;

    EXPECT( to_value( x ) == 0 );
}

CASE( "numeric: Allows to custom-default-construct a numeric thus defined" )
{
    typedef numeric< int, struct Tag, custom_default_t< int, 5 > > CustomDefaultNumeric;
    CustomDefaultNumeric x;

    EXPECT( to_value( x ) == 5 );
}

CASE( "numeric: Allows to copy-construct a numeric from its underlying type" )
{
    CopyMoveNumeric x( CopyMove(7) );

    EXPECT( to_value( x ) == CopyMove(7) );
}

CASE( "numeric: Allows to move-construct a numeric from its underlying type (C++11)" )
{
#if type_CPP11_OR_GREATER
    MoveOnlyNumeric x( MoveOnly{42} );

    EXPECT( to_value( x ).v == 42 );
#else
    EXPECT( !!"numeric: move-construction is not available (no C++11)" );
#endif
}

CASE( "numeric: Allows to compare a numeric for equality" )
{
    CopyMoveNumeric x( CopyMove( 7) );
    CopyMoveNumeric y( CopyMove(42) );

    EXPECT( x == x );
    EXPECT( x != y );
}

CASE( "numeric: Allows to compare a numeric for order" )
{
    CopyMoveNumeric x( CopyMove( 7) );
    CopyMoveNumeric y( CopyMove(42) );

    EXPECT( x <  y );
    EXPECT( x <= x );
    EXPECT( y >  x );
    EXPECT( y >= y );
}

CASE( "numeric: Allows to apply unary+, unary-" )
{
    Numeric x( 7 );

    EXPECT( +x == Numeric( 7) );
    EXPECT( -x == Numeric(-7) );
}

CASE( "numeric: Allows to apply pre- and post-increment and -decrement" )
{
    SETUP("") {
        Numeric x(7);

    SECTION("") {
        EXPECT( ++x == Numeric(8) );
    }
    SECTION("") {
        EXPECT( --x == Numeric(6) );
    }
    SECTION("") {
        EXPECT( x++ == Numeric(7) );
    }
    SECTION("") {
        EXPECT( x-- == Numeric(7) );
    }}
}

CASE( "numeric: Allows to add, subtract, multiply, divide, rest-divide numerics (x op y)" )
{
    SETUP("") {
        Numeric::underlying_type xu(7);
        Numeric::underlying_type yu(9);
        Numeric x(xu);
        Numeric y(yu);

    SECTION("") {
        EXPECT( y + x == Numeric(yu + xu) );
    }
    SECTION("") {
        EXPECT( y - x == Numeric(yu - xu) );
    }
    SECTION("") {
        EXPECT( y * x == Numeric(yu * xu) );
    }
    SECTION("") {
        EXPECT( y / x == Numeric(yu / xu) );
    }
    SECTION("") {
        EXPECT( y % x == Numeric(yu % xu) );
    }}
}

CASE( "numeric: Allows to add, subtract, multiply, divide, rest-divide numerics (x op= y)" )
{
    SETUP("") {
        Numeric::underlying_type xu(7);
        Numeric::underlying_type yu(9);
        Numeric x(xu);
        Numeric y(yu);

    SECTION("") {
        EXPECT( (y += x) == Numeric(yu + xu) );
    }
    SECTION("") {
        EXPECT( (y -= x) == Numeric(yu - xu) );
    }
    SECTION("") {
        EXPECT( (y *= x) == Numeric(yu * xu) );
    }
    SECTION("") {
        EXPECT( (y /= x) == Numeric(yu / xu) );
    }
    SECTION("") {
        EXPECT( (y %= x) == Numeric(yu % xu) );
    }}
}

CASE( "numeric: Allows to obtain hash of a numeric object (C++11)" )
{
#if type_CPP11_OR_GREATER
    EXPECT( make_hash( Numeric(7) ) != make_hash( Numeric(9) ) );
#else
    EXPECT( !!"type: std::hash is not available (no C++11)" );
#endif
}

// -----------------------------------------------------------------------
// quantity:

typedef quantity< int, struct Tag > Quantity;
typedef quantity< CopyMove, struct Tag > CopyMoveQuantity;
typedef quantity< MoveOnly, struct Tag > MoveOnlyQuantity;

CASE( "quantity: Disallows to default-construct a quantity thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    quantity< int, struct Tag, no_default_t > x;
#endif
    EXPECT( true );
}

CASE( "quantity: Allows to default-construct a quantity thus defined" )
{
    Quantity x;

    EXPECT( to_value( x ) == 0 );
}

CASE( "quantity: Allows to custom-default-construct a quantity thus defined" )
{
    typedef quantity< int, struct Tag, custom_default_t< int, 5 > > CustomDefaultQuantity;
    CustomDefaultQuantity x;

    EXPECT( to_value( x ) == 5 );
}

CASE( "quantity: Allows to copy-construct a quantity from its underlying type" )
{
    CopyMoveQuantity x( CopyMove(7) );

    EXPECT( to_value( x ) == CopyMove(7) );
}

CASE( "quantity: Allows to move-construct a quantity from its underlying type (C++11)" )
{
#if type_CPP11_OR_GREATER
    MoveOnlyQuantity x( MoveOnly{42} );

    EXPECT( to_value( x ).v == 42 );
#else
    EXPECT( !!"quantity: move-construction is not available (no C++11)" );
#endif
}

CASE( "quantity: Allows to compare a numeric for equality" )
{
    CopyMoveQuantity x( CopyMove( 7) );
    CopyMoveQuantity y( CopyMove(42) );

    EXPECT( x == x );
    EXPECT( x != y );
}

CASE( "quantity: Allows to compare a numeric for order" )
{
    CopyMoveQuantity x( CopyMove( 7) );
    CopyMoveQuantity y( CopyMove(42) );

    EXPECT( x <  y );
    EXPECT( x <= x );
    EXPECT( y >  x );
    EXPECT( y >= y );
}

CASE( "quantity: Allows to apply unary+, unary-" )
{
    Quantity x( 7 );

    EXPECT( +x == Quantity( 7) );
    EXPECT( -x == Quantity(-7) );
}

CASE( "quantity: Allows to add, subtract quantities (x op y)" )
{
    SETUP("") {
        Quantity::underlying_type xu(7);
        Quantity::underlying_type yu(9);
        Quantity x(xu);
        Quantity y(yu);

    SECTION("") {
        EXPECT( y + x == Quantity(yu + xu) );
    }
    SECTION("") {
        EXPECT( y - x == Quantity(yu - xu) );
    }}
}

CASE( "quantity: Allows to add, subtract quantities (x op= y)" )
{
    SETUP("") {
        Quantity::underlying_type xu(7);
        Quantity::underlying_type yu(9);
        Quantity x(xu);
        Quantity y(yu);

    SECTION("") {
        EXPECT( (y += x) == Quantity(yu + xu) );
    }
    SECTION("") {
        EXPECT( (y -= x) == Quantity(yu - xu) );
    }}
}

CASE( "quantity: Disallows to multiply a quantity with a quantity" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    Quantity(3) * Quantity(4);
#endif
}

CASE( "quantity: Allows to multiply a quantity with a scalar (result: quantity)" )
{
    Quantity::underlying_type a(9);
    Quantity::underlying_type xu(7);
    Quantity x(xu);

    EXPECT( a * x == Quantity(a * xu) );
    EXPECT( x * a == Quantity(a * xu) );
}

CASE( "quantity: Allows to divide a quantity by a scalar (result: quantity)" )
{
    Quantity::underlying_type a(9);
    Quantity::underlying_type xu(7);
    Quantity x(xu);

    EXPECT( x / a == Quantity(xu / a) );
}

CASE( "quantity: Allows to divide a quantity by a quantity (result: scalar)" )
{
    Quantity::underlying_type xu( 7);
    Quantity::underlying_type yu(21);
    Quantity x(xu);
    Quantity y(yu);

    EXPECT( y / x == (yu / xu) );
}

CASE( "quantity: Allows to obtain hash of a quantity object (C++11)" )
{
#if type_CPP11_OR_GREATER
    EXPECT( make_hash( Quantity(7) ) != make_hash( Quantity(9) ) );
#else
    EXPECT( !!"type: std::hash is not available (no C++11)" );
#endif
}

// -----------------------------------------------------------------------
// address:

typedef address<    int *, std::ptrdiff_t, struct Tag > Address;
typedef Address::offset_type OffsetType;

typedef address< CopyMove, std::ptrdiff_t, struct Tag > CopyMoveAddress;
typedef address< MoveOnly, std::ptrdiff_t, struct Tag > MoveOnlyAddress;

CASE( "address: Disallows to default-construct an address thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    address< int *, std::ptrdiff_t, struct Tag, no_default_t > x;
#endif
    EXPECT( true );
}

CASE( "address: Allows to default-construct an address thus defined" )
{
    address< int *, std::ptrdiff_t, struct Tag > x;

#if type_CPP11_OR_GREATER
    EXPECT( to_value( x ) == nullptr );
#else
    EXPECT( to_value( x ) == (void*)NULL );
#endif
}

int sample = 0;

CASE( "address: Allows to custom-default-construct a address thus defined" )
{
    typedef address< int*, std::ptrdiff_t, struct Tag, custom_default_t< int*, &sample > > CustomDefaultAddress;
    CustomDefaultAddress x;

    EXPECT( to_value( x ) == &sample );
}

CASE( "address: Allows to copy-construct an address from its underlying type" )
{
    int i;
    address< int *, std::ptrdiff_t, struct Tag > x( &i );

    EXPECT( to_value( x ) == &i );
}

CASE( "address: Allows to move-construct an address from its underlying type (C++11)" )
{
#if type_CPP11_OR_GREATER
    address< MoveOnly, std::ptrdiff_t, struct Tag > x( MoveOnly{42} );

    EXPECT( to_value( x ).v == 42 );
#else
    EXPECT( !!"address: move-construction is not available (no C++11)" );
#endif
}

CASE( "address: Disallows to add addresses" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    int i;
    Address(&i) + Address(&i);
#endif
    EXPECT( true );
}

CASE( "address: Allows to subtract addresses to yield an offset (a - a)" )
{
    int i;

    EXPECT( Address(&i) - Address(&i) == OffsetType(0) );
}

CASE( "address: Allows to add, subtract an offset (a + o, a - o)" )
{
    SETUP("") {
        int i[3];
        Address a( &i[1] );
        OffsetType o( 1 );

    SECTION("") {
        EXPECT( a + o == Address(&i[1] + 1) );
    }
    SECTION("") {
        EXPECT( a - o == Address(&i[1] - 1) );
    }}
}

CASE( "address: Allows to add, subtract an offset (a += o, a -= o)" )
{
    SETUP("") {
        int i[3];
        Address a( &i[1] );
        OffsetType o( 1 );

    SECTION("") {
        EXPECT( (a += o) == Address(&i[1] + 1) );
    }
    SECTION("") {
        EXPECT( (a -= o) == Address(&i[1] - 1) );
    }}
}

CASE( "address: Allows to an offset and an addresses (a + o, o + a)" )
{
    int i[3];

    EXPECT( Address(&i[1]) + OffsetType(1)  == Address(&i[1]+1) );
    EXPECT( OffsetType(1)  + Address(&i[1]) == Address(&i[1]+1) );
}

CASE( "address: Allows to subtract an offset from an address (a - o)" )
{
    int i[2];

    EXPECT( Address(&i[1]) - OffsetType(1) == Address(&i[1]-1) );
}

CASE( "address: Disallows to subtract an addresses from an offset" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    OffsetType(0) - Address(0);
#endif
    EXPECT( true );
}

CASE( "address: Allows to obtain hash of an address object (C++11)" )
{
#if type_CPP11_OR_GREATER
    int i, k;
    EXPECT( make_hash( Address(&i) ) != make_hash( Address(&k) ) );
#else
    EXPECT( !!"type: std::hash is not available (no C++11)" );
#endif
}

// -----------------------------------------------------------------------
// offset:

typedef offset< int, struct Tag > Offset;
typedef offset< CopyMove, struct Tag > CopyMoveOffset;
typedef offset< MoveOnly, struct Tag > MoveOnlyOffset;

CASE( "offset: Disallows to default-construct an offset thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if type_CONFIG_CONFIRMS_COMPILATION_ERRORS
    offset< int, struct Tag, no_default_t > x;
#endif
}

CASE( "offset: Allows to default-construct an offset thus defined" )
{
    Offset x;

    EXPECT( to_value( x ) == 0 );
}

CASE( "offset: Allows to custom-default-construct a offset thus defined" )
{
    typedef offset< int, struct Tag, custom_default_t< int, 5 > > CustomDefaultOffset;
    CustomDefaultOffset x;

    EXPECT( to_value( x ) == 5 );
}

CASE( "offset: Allows to copy-construct an offset from its underlying type" )
{
    CopyMoveOffset x( CopyMove(7) );

    EXPECT( to_value( x ) == CopyMove(7) );
}

CASE( "offset: Allows to move-construct an offset from its underlying type (C++11)" )
{
#if type_CPP11_OR_GREATER
    MoveOnlyOffset x( MoveOnly{42} );

    EXPECT( to_value( x ).v == 42 );
#else
    EXPECT( !!"offset: move-construction is not available (no C++11)" );
#endif
}

CASE( "offset: Allows to add, subtract offsets (x op y)" )
{
    SETUP("") {
        Offset x(7);
        Offset y(9);

    SECTION("") {
        EXPECT( y + x == Offset(9 + 7) );
    }
    SECTION("") {
        EXPECT( y - x == Offset(9 - 7) );
    }}
}

CASE( "offset: Allows to add, subtract offsets (x op= y)" )
{
    SETUP("") {
        Offset x(7);
        Offset y(9);

    SECTION("") {
        EXPECT( (y += x) == Offset(9 + 7) );
    }
    SECTION("") {
        EXPECT( (y -= x) == Offset(9 - 7) );
    }}
}

CASE( "offset: Allows to obtain hash of an offset object (C++11)" )
{
#if type_CPP11_OR_GREATER
    EXPECT( make_hash( Offset(7) ) != make_hash( Offset(9) ) );
#else
    EXPECT( !!"type: std::hash is not available (no C++11)" );
#endif
}

// -----------------------------------------------------------------------
// macros:

// prevent warning "uses local type" for tag in C++98:

type_DECLARE_TAG( Quantity )
type_DECLARE_TAG( QuantityA)
type_DECLARE_TAG( Ordered  )
type_DECLARE_TAG( Integer  )
type_DECLARE_TAG( Day      )

CASE( "macro: type_DEFINE_TYPE(Strong, type, native)" )
{
    type_DEFINE_TYPE( Quantity, quantity, double )

    EXPECT( ( Quantity() < Quantity(7) ) );
}

CASE( "macro: type_DEFINE_TYPE_ND(Strong, type, native)" )
{
    type_DEFINE_TYPE_ND( Ordered, ordered, int )

    EXPECT( ( Ordered(7) == Ordered(7) ) );
}

CASE( "macro: type_DEFINE_SUBTYPE(Sub, Super)" )
{
#if type_CPP11_OR_GREATER
    type_DEFINE_TYPE(               Quantity , quantity, double )
    type_DEFINE_SUBTYPE( QuantityA, Quantity )

    EXPECT( ( QuantityA() < QuantityA(7) ) );
#else
    // prevent warning "uses local type" in C++98:
    struct S {
        type_DEFINE_TYPE(               Quantity , quantity, double )
        type_DEFINE_SUBTYPE( QuantityA, Quantity )
    };

    EXPECT( ( S::QuantityA() < S::QuantityA(7) ) );
#endif
}

CASE( "macro: type_DEFINE_SUBTYPE_ND(Sub, Super)" )
{
#if type_CPP11_OR_GREATER
    type_DEFINE_TYPE_ND(         Ordered, ordered, int )
    type_DEFINE_SUBTYPE_ND( Day, Ordered )

    EXPECT( ( Day(7) == Day(7) ) );
#else
    // prevent warning "uses local type" in C++98:
    struct S {
        type_DEFINE_TYPE_ND(         Ordered, ordered, int )
        type_DEFINE_SUBTYPE_ND( Day, Ordered )
    };

    EXPECT( ( S::Day(7) == S::Day(7) ) );
#endif
}

CASE( "macro: type_DEFINE_FUNCTION(Strong, StrongFunction, function)" )
{
    struct S {
        type_DEFINE_TYPE_ND(         Integer, numeric, int  )
        static type_DEFINE_FUNCTION( Integer, abs, std::abs )
    };

    EXPECT( ( S::abs( S::Integer(-7) ) == S::Integer(7) ) );
}

CASE( "macro: type_DEFINE_FUNCTION_CE(Strong, StrongFunction, function)" )
{
    struct S {
        type_DEFINE_TYPE_ND(            Integer, numeric, int  )
        static type_DEFINE_FUNCTION_CE( Integer, negate , negate )

        static type_constexpr14 int negate( int v ) { return -v; }
    };

    EXPECT( ( S::negate( S::Integer(7) ) == S::Integer(-7) ) );
}

} // anonymous namespace
