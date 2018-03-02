//
// type, strong types for C++98 and later.
// For more information see https://github.com/martinmoene/type
//
// Copyright (c) 2018 Martin Moene
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef NONSTD_TYPE_HPP_INCLUDED
#define NONSTD_TYPE_HPP_INCLUDED

#define  type_VERSION "0.0.0"

// nonstd type configuration:

// (none)

// Compiler detection (C++20 is speculative):
// Note: MSVC supports C++14 since it supports C++17.

#ifdef _MSVC_LANG
# define type_MSVC_LANG  _MSVC_LANG
#else
# define type_MSVC_LANG  0
#endif

#define type_CPP11             (__cplusplus == 201103L )
#define type_CPP11_OR_GREATER  (__cplusplus >= 201103L || type_MSVC_LANG >= 201103L )
#define type_CPP14_OR_GREATER  (__cplusplus >= 201402L || type_MSVC_LANG >= 201703L )
#define type_CPP17_OR_GREATER  (__cplusplus >= 201703L || type_MSVC_LANG >= 201703L )
#define type_CPP20_OR_GREATER  (__cplusplus >= 202000L || type_MSVC_LANG >= 202000L )

// Compiler versions:
//
// MSVC++ 6.0  _MSC_VER == 1200 (Visual Studio 6.0)
// MSVC++ 7.0  _MSC_VER == 1300 (Visual Studio .NET 2002)
// MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio .NET 2003)
// MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
// MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
// MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
// MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
// MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
// MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
// MSVC++ 14.1 _MSC_VER >= 1910 (Visual Studio 2017)

#if defined(_MSC_VER) && !defined(__clang__)
# define type_COMPILER_MSVC_VERSION   (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900)) )
#else
# define type_COMPILER_MSVC_VERSION   0
#endif

#define type_COMPILER_VERSION( major, minor, patch )  (10 * ( 10 * major + minor) + patch)

#if defined __clang__
# define type_COMPILER_CLANG_VERSION  type_COMPILER_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#else
# define type_COMPILER_CLANG_VERSION    0
#endif

#if defined __GNUC__
# define type_COMPILER_GNUC_VERSION  type_COMPILER_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#else
# define type_COMPILER_GNUC_VERSION    0
#endif

// half-open range [lo..hi):
#define type_BETWEEN( v, lo, hi ) ( lo <= v && v < hi )

// Presence of C++11 language features:

#if type_CPP11_OR_GREATER || type_COMPILER_MSVC_VERSION >= 140
# define type_HAVE_ALIAS_TEMPLATE  1
# define type_HAVE_CONSTEXPR_11  1
# define type_HAVE_EXPLICIT_CONVERSION  1
# define type_HAVE_INLINE_NAMESPACE  1
# define type_HAVE_IS_DEFAULT  1
# define type_HAVE_IS_DELETE  1
# define type_HAVE_NOEXCEPT  1
# define type_HAVE_REF_QUALIFIER  1
# define type_HAVE_UNICODE_LITERALS  1
# define type_HAVE_USER_DEFINED_LITERALS  1
# if ! ( ( type_CPP11 && type_COMPILER_CLANG_VERSION ) || type_BETWEEN( type_COMPILER_CLANG_VERSION, 300, 400 ) )
#  define type_HAVE_STD_DEFINED_LITERALS  1
# endif
#endif

// Presence of C++14 language features:

#if type_CPP14_OR_GREATER
# define type_HAVE_CONSTEXPR_14  1
#endif

// For the rest, consider VC14 as C++11 for optional-lite:

#if      type_COMPILER_MSVC_VERSION >= 140
# undef  type_CPP11_OR_GREATER
# define type_CPP11_OR_GREATER  1
#endif

// Presence of C++ library features:

#if type_CPP11_OR_GREATER || type_COMPILER_MSVC_VERSION >= 120
# define type_HAVE_STD_HASH  1
#endif

// C++ feature usage:

#if      type_HAVE_CONSTEXPR_11
# define type_constexpr  constexpr
#else
# define type_constexpr  /*constexpr*/
#endif

#if      type_HAVE_CONSTEXPR_14
# define type_constexpr14  constexpr
#else
# define type_constexpr14  /*constexpr*/
#endif

#if      type_HAVE_EXPLICIT_CONVERSION
# define type_explicit  explicit
#else
# define type_explicit  /*explicit*/
#endif

#if      type_HAVE_INLINE_NAMESPACE
# define type_inline_ns  inline
#else
# define type_inline_ns  /*inline*/
#endif

#if      type_HAVE_IS_DELETE
# define type_is_delete = delete
#else
# define type_is_delete
#endif

#if      type_HAVE_IS_DELETE
# define type_is_delete_access public
#else
# define type_is_delete_access private
#endif

#if      type_HAVE_NOEXCEPT
# define type_noexcept  noexcept
#else
# define type_noexcept  /*noexcept*/
#endif

// Additional includes:

#include <ostream>

#if type_CPP11_OR_GREATER
# include <functional>      // std::hash<>
# include <utility>         // std::move()
# include <type_traits>     // std::is_nothrow_move_constructible<>
#endif

/**
 * define a default-constructable type.
 */
#define type_DEFINE_TYPE_DEFAULT( type_name, type_type, underlying_type ) \
    typedef ::nonstd::type_type<underlying_type, struct type_name##_tag> type_name;

/**
 * define a non-default-constructable type.
 */
#define type_DEFINE_TYPE( type_name, type_type, underlying_type ) \
    typedef ::nonstd::type_type<underlying_type, struct type_name##_tag, ::nonstd::no_default_t> type_name;

/**
 * define a default-constructable sub-type.
 */
#define type_DEFINE_SUBTYPE_DEFAULT( sub, super ) \
    struct sub : super { \
        type_constexpr explicit sub(underlying_type const & x = underlying_type() ) : super(x) {} \
    };

/**
 * define a non-default-constructable sub-type.
 */
#define type_DEFINE_SUBTYPE( sub, super ) \
    struct sub : super { \
        type_constexpr explicit sub(underlying_type const & x) : super(x) {} \
    };

/**
 * define a function for given type.
 */
#define type_DEFINE_FUNCTION( type_type, type_function, function ) \
    inline type_constexpr14 type_type type_function( type_type const & x )   \
    {   \
        return type_type( function( x.get() ) );    \
    }

// For C++11 and later, put default with move constructor, 
// otherwise put it with the copy constructor.
    
#if type_CPP11_OR_GREATER
# define type_DEFAULT98( expr )
#else
# define type_DEFAULT98( expr )   = expr
#endif

namespace nonstd { namespace types {

// EqualityComparable, comparation functions based on operator==() and operator<():

template< typename T, typename U = T > struct is_eq   { friend type_constexpr14 bool operator==( T const & x, U const & y ) { return x.get() == y.get(); } };
template< typename T, typename U = T > struct is_lt   { friend type_constexpr14 bool operator==( T const & x, U const & y ) { return x.get() <  y.get();  } };

template< typename T, typename U = T > struct is_ne   { friend type_constexpr14 bool operator!=( T const & x, U const & y ) { return ! ( x == y ); } };
template< typename T, typename U = T > struct is_lteq { friend type_constexpr14 bool operator> ( T const & x, U const & y ) { return     y < x;    } };
template< typename T, typename U = T > struct is_gt   { friend type_constexpr14 bool operator<=( T const & x, U const & y ) { return ! ( y < x ); } };
template< typename T, typename U = T > struct is_gteq { friend type_constexpr14 bool operator>=( T const & x, U const & y ) { return ! ( x < y ); } };

// Logical operations:

template< typename R, typename T = R > struct logical_not{ friend type_constexpr14 R operator!( T const & x ) { return R( ! x.get() ); } };

template< typename R, typename T = R, typename U = R > struct logical_and{ friend type_constexpr14 R operator&&( T const & x, U const & y ) { return R( x.get() && y.get() ); } };
template< typename R, typename T = R, typename U = R > struct logical_or { friend type_constexpr14 R operator||( T const & x, U const & y ) { return R( x.get() || y.get() ); } };

// Arithmetic operations based on operator X=():

template< typename R, typename T = R, typename U = R > struct plus       { friend type_constexpr14 R operator+( T x, U const & y ) { return x += y; } };
template< typename R, typename T = R, typename U = R > struct plus2      { friend type_constexpr14 R operator+( T const & x, U y ) { return y += x; } };
template< typename R, typename T = R, typename U = R > struct minus      { friend type_constexpr14 R operator-( T x, U const & y ) { return x -= y; } };
template< typename R, typename T = R, typename U = R > struct multiplies { friend type_constexpr14 R operator*( T x, U const & y ) { return x *= y; } };
template< typename R, typename T = R, typename U = R > struct multiplies2{ friend type_constexpr14 R operator*( T const & x, U y ) { return y *= x; } };
template< typename R, typename T = R, typename U = R > struct divides    { friend type_constexpr14 R operator/( T x, U const & y ) { return x /= y; } };
template< typename R, typename T = R, typename U = R > struct modulus    { friend type_constexpr14 R operator%( T x, U const & y ) { return x %= y; } };

// Bitwise operations based on operator X=():

template< typename R, typename T = R, typename U = R > struct bit_and { friend type_constexpr14 R operator&( T x, U const & y ) { return x &= y; } };
template< typename R, typename T = R, typename U = R > struct bit_or  { friend type_constexpr14 R operator|( T x, U const & y ) { return x |= y; } };
template< typename R, typename T = R, typename U = R > struct bit_xor { friend type_constexpr14 R operator^( T x, U const & y ) { return x ^= y; } };

template< typename R, typename T = R > struct bit_shl { friend type_constexpr14 R operator<<( T x, int const n ) { return x <<= n; } };
template< typename R, typename T = R > struct bit_shr { friend type_constexpr14 R operator>>( T x, int const n ) { return x >>= n; } };

/**
 * disallow default construction.
 */
struct no_default_t{};

/**
 * data base class
 */
template< typename T, typename D = T >
struct data
{
    typedef T underlying_type;

    type_constexpr explicit data( T const & v type_DEFAULT98( D() ) )
        : value( v )
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit data( T && v = D() ) noexcept( noexcept(std::is_nothrow_move_constructible<T>::value) )
        : value( std::move( v ) )
    {}
#endif

    type_constexpr14 T       & get()       { return value; }
    type_constexpr14 T const & get() const { return value; }

#if type_CPP11_OR_GREATER
    type_constexpr14 void swap( data & other )
    {
        auto tmp{ std::move( other.get() ) };
        other.get() = std::move( this->get() );
        this->get() = std::move( tmp );
    }
#else
    void swap( data & other )
    {
        using std::swap;
        swap( this->get(), other.get() );
    }
#endif

private:
    underlying_type value;
};

/**
 * type, no operators.
 */
template< typename T, typename Tag, typename D = T >
struct type : data<T,D>
{
    type_constexpr explicit type( T const & v type_DEFAULT98( D() ) )
        : data<T,D>( v )
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit type( T && v = D() ) noexcept( noexcept(std::is_nothrow_move_constructible<T>::value) )
        : data<T,D>( std::move( v ) )
    {}
#endif
};

/**
 * boolean.
 */
template< typename Tag, typename D = bool >
struct boolean
    : type < bool,Tag,D >
    , is_eq< boolean<Tag,D> >
    , is_ne< boolean<Tag,D> >
{
private:
    // explicit boolean operator return type.

    typedef void ( boolean::*bool_type )() const;

    // address of method used as 'boolean',

    void ERROR_this_type_does_not_support_comparisons() const {}

public:
    // default/initializing constructor.

    type_constexpr explicit boolean( bool value = D() )
        : type<bool,Tag,D>( value )
    {}

    // safe conversion to 'boolean';

#if type_HAVE_EXPLICIT_CONVERSION
    type_constexpr explicit operator bool() const
    {
        return this->get();
    }
#else
    type_constexpr operator bool_type() const
    {
        return this->get() ? &boolean::ERROR_this_type_does_not_support_comparisons : 0;
    }
#endif
};

/**
 * logical, ...
 */
template< typename T, typename Tag, typename D = T >
struct logical
    : type< T,Tag,D >
    , logical_not< type<T,Tag,D> >
    , logical_and< type<T,Tag,D> >
    , logical_or < type<T,Tag,D> >
{
    type_constexpr explicit logical( T const & v type_DEFAULT98( D() ) )
        : type<T,Tag,D>( v )
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit logical( T && v = D() ) noexcept( noexcept(std::is_nothrow_move_constructible<T>::value) )
        : type<T,Tag,D>( std::move( v ) )
    {}
#endif

    type_constexpr logical( type<T,Tag,D> const & other )
        : type<T,Tag,D>( other.get() )
    {}
};

/**
 * equality, EqualityComparable.
 */
template< typename T, typename Tag, typename D = T >
struct equality
    : type<T,Tag,D>
    , is_eq< equality<T,Tag,D> >
    , is_ne< equality<T,Tag,D> >
{
    type_constexpr explicit equality( T const & v type_DEFAULT98( D() ) )
        : type<T,Tag,D>( v )
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit equality( T && v = D() ) noexcept( noexcept(std::is_nothrow_move_constructible<T>::value) )
        : type<T,Tag,D>( std::move( v ) )
    {}
#endif

    type_constexpr equality( type<T,Tag,D> const & other )
        : type<T,Tag,D>( other.get() )
    {}
};

/**
 * bits, EqualityComparable and bitwise operators.
 */
template< typename T, typename Tag, typename D = T >
struct bits
    : equality< T,Tag,D >
    , bit_and < bits<T,Tag,D> >
    , bit_or  < bits<T,Tag,D> >
    , bit_xor < bits<T,Tag,D> >
    , bit_shl < bits<T,Tag,D> >
    , bit_shr < bits<T,Tag,D> >
{
    type_constexpr explicit bits( T const & v type_DEFAULT98( D() ) )
        : equality<T,Tag,D>( v )
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit bits( T && v = D() ) noexcept( noexcept(std::is_nothrow_move_constructible<T>::value) )
        : equality<T,Tag,D>( std::move( v ) )
    {}
#endif

    type_constexpr bits( type<T,Tag,D> const & other )
        : equality<T,Tag,D>( other.get() )
    {}

    type_constexpr14 bits & operator^=( bits const & other ) { this->get() ^= other.get(); return *this; }
    type_constexpr14 bits & operator&=( bits const & other ) { this->get() &= other.get(); return *this; }
    type_constexpr14 bits & operator|=( bits const & other ) { this->get() |= other.get(); return *this; }

    type_constexpr14 bits & operator<<=( int const n ) { this->get() <<= n; return *this; }
    type_constexpr14 bits & operator>>=( int const n ) { this->get() >>= n; return *this; }
};

/**
 * ordered, LessThanComparable.
 */
template< typename T, typename Tag, typename D = T >
struct ordered
    : equality<T,Tag,D>
    , is_lt   < ordered<T,Tag,D> >
    , is_gt   < ordered<T,Tag,D> >
    , is_lteq < ordered<T,Tag,D> >
    , is_gteq < ordered<T,Tag,D> >
{
    type_constexpr explicit ordered( T const & v type_DEFAULT98( D() ) )
        : equality<T,Tag,D>( v )
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit ordered( T && v = D() ) noexcept( noexcept(std::is_nothrow_move_constructible<T>::value) )
        : equality<T,Tag,D>( std::move( v ) )
    {}
#endif

    type_constexpr ordered( type<T,Tag,D> const & other )
        : equality<T,Tag,D>( other.get() )
    {}
};

/**
 * numeric, LessThanComparable and ...
 */
template< typename T, typename Tag, typename D = T >
struct numeric
    : ordered   < T,Tag,D >
    , plus      < numeric<T,Tag,D> >
    , minus     < numeric<T,Tag,D> >
    , multiplies< numeric<T,Tag,D> >
    , divides   < numeric<T,Tag,D> >
    , modulus   < numeric<T,Tag,D> >
{
    type_constexpr explicit numeric( T const & v type_DEFAULT98( D() ) )
        : ordered<T,Tag,D>( v )
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit numeric( T && v = D() ) noexcept( noexcept(std::is_nothrow_move_constructible<T>::value) )
        : ordered<T,Tag,D>( std::move( v ) )
    {}
#endif

    type_constexpr numeric( type<T,Tag,D> const & other )
        : ordered<T,Tag,D>( other.get() )
    {}

    type_constexpr14 numeric operator+() const { return *this; }
    type_constexpr14 numeric operator-() const { return numeric( -this->get() ); }

    type_constexpr14 numeric & operator++() { return ++this->get(), *this; }
    type_constexpr14 numeric & operator--() { return --this->get(), *this; }

    type_constexpr14 numeric   operator++( int ) { numeric tmp(*this); ++*this; return tmp; }
    type_constexpr14 numeric   operator--( int ) { numeric tmp(*this); --*this; return tmp; }

    type_constexpr14 numeric & operator+=( numeric const & other ) { this->get() += other.get(); return *this; }
    type_constexpr14 numeric & operator-=( numeric const & other ) { this->get() -= other.get(); return *this; }
    type_constexpr14 numeric & operator*=( numeric const & other ) { this->get() *= other.get(); return *this; }
    type_constexpr14 numeric & operator/=( numeric const & other ) { this->get() /= other.get(); return *this; }
    type_constexpr14 numeric & operator%=( numeric const & other ) { this->get() %= other.get(); return *this; }
};

/**
 * quantity, keep dimension.
 */
template< typename T, typename Tag, typename D = T >
struct quantity
    : numeric    < T,Tag,D >
    , multiplies < quantity<T,Tag,D>,    quantity<T,Tag,D>, T >
    , multiplies2< quantity<T,Tag,D>, T, quantity<T,Tag,D>    >
    , divides    < quantity<T,Tag,D>,    quantity<T,Tag,D>, T >
{
    explicit quantity( T const & v type_DEFAULT98( D() ) )
        : numeric<T,Tag,D>( v )
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit quantity( T && v = D() ) noexcept( noexcept(std::is_nothrow_move_constructible<T>::value) )
        : numeric<T,D>( std::move( v ) )
    {}
#endif

    type_constexpr quantity( type<T,Tag,D> const & other )
        : numeric<T,Tag,D>( other.get() )
    {}

    type_constexpr14 quantity & operator*=( T const & y ) { return this->get() *= y, *this; }
    type_constexpr14 quantity & operator/=( T const & y ) { return this->get() /= y, *this; }

    type_constexpr14 T operator/( quantity const & y ) { return this->get() / y.get(); }

type_is_delete_access:
    quantity & operator*=( quantity const & ) type_is_delete;
};

/**
 * offset for address calculations.
 *
 * offset + offset  => offset
 * offset - offset  => offset
 */
template< typename T, typename Tag, typename D = T >
struct offset
    : ordered< T,Tag,D >
    , plus   < offset<T,Tag,D> >
    , minus  < offset<T,Tag,D> >
{
    type_constexpr explicit offset( T const & v type_DEFAULT98( D() ) )
        : ordered<T,Tag,D>( v )
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit offset( T && v = D() ) noexcept( noexcept(std::is_nothrow_move_constructible<T>::value) )
        : ordered<T,Tag,D>( std::move( v ) )
    {}
#endif

    type_constexpr14 offset & operator+=( offset const & y ) { this->get() += y.get(); return *this; }
    type_constexpr14 offset & operator-=( offset const & y ) { this->get() -= y.get(); return *this; }
};

/**
 * address
 *
 * address + address => error
 * address - address => offset
 * address + offset  => address
 * address - offset  => address
 *  offset + address => address
 *  offset - address https://github.com/sxs-collaboration/spectre=> error
 *  offset + offset  => offset
 *  offset - offset  => offset
 */
template< typename T, typename O, typename Tag, typename D = T >
struct address
    : ordered< T,Tag,D >
    , plus < address<T,O,Tag,D>, address<T,O,Tag,D>, offset <  O,Tag,O> >
    , plus2< address<T,O,Tag,D>, offset <  O,Tag,O>, address<T,O,Tag,D> >
    , minus< address<T,O,Tag,D>, address<T,O,Tag,D>, offset <  O,Tag,O> >
{
    typedef offset<O,Tag,O> offset_type;

    type_constexpr explicit address( T const & v type_DEFAULT98( D() ) )
        : ordered<T,Tag,D>( v )
    {}

#if type_CPP11_OR_GREATER
    type_constexpr explicit address( T && v = D() ) noexcept( noexcept(std::is_nothrow_move_constructible<T>::value) )
        : ordered<T,Tag,D>( std::move( v ) )
    {}
#endif

    type_constexpr14 address & operator+=( offset_type const & y ) { this->get() += y.get(); return *this; }
    type_constexpr14 address & operator-=( offset_type const & y ) { this->get() -= y.get(); return *this; }

    friend type_constexpr14 offset_type operator-( address const & x, address const & y ) { return offset_type( x.get() - y.get() ); }

type_is_delete_access:
    void operator+=( address const & ) type_is_delete;
};

// swap values.

template < typename T, typename Tag, typename D >
inline type_constexpr14 void swap( type<T,Tag,D> & x, type<T,Tag,D> & y )
{
    x.swap( y );
}

// the underlying value.

template< typename T, typename Tag, typename D >
inline type_constexpr14 typename type<T,Tag,D>::underlying_type
to_value( type<T,Tag,D> const & v )
{
    return v.get();
}

// stream output.

template< typename T, typename Tag, typename D >
inline std::ostream & operator<<( std::ostream & os, type<T,Tag,D> v )
{
    return os << v.get();
}

}}  // namespace nonstd::types

#if type_HAVE_STD_HASH

namespace std {

template< typename T, typename Tag, typename D >
struct hash< nonstd::types::type<T,Tag,D> >
{
public:
    std::size_t operator()( nonstd::types::type<T,Tag,D> const & v ) const type_noexcept
    {
        return std::hash<T>( v.get() );
    }
};

template< typename T, typename Tag, typename D >
struct hash< nonstd::types::numeric<T,Tag,D> >
{
public:
    std::size_t operator()( nonstd::types::numeric<T,Tag,D> const & v ) const type_noexcept
    {
        return std::hash<T>( v.get() );
    }
};

}  // namespace std

#endif

// make type available in namespace nonstd:

namespace nonstd {

using types::no_default_t;

using types::type;
using types::bits;
using types::boolean;
using types::logical;
using types::equality; // equal
using types::ordered;
using types::numeric;
using types::quantity;

using types::offset;
using types::address;

using types::swap;

using types::operator<<;

} // namespace nonstd

#endif // NONSTD_TYPE_HPP_INCLUDED
