# type: A tiny single-file header-only library for strong types for C++98, C++11 and later 

[![Language](https://img.shields.io/badge/C%2B%2B-98/11/14/17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://travis-ci.org/martinmoene/type-lite.svg?branch=master)](https://travis-ci.org/martinmoene/type-lite) [![Build status](https://ci.appveyor.com/api/projects/status/1ha3wnxtam547m8p?svg=true)](https://ci.appveyor.com/project/martinmoene/type-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Ftype-lite.svg)](https://github.com/martinmoene/type-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://github.com/martinmoene/type-lite/blob/master/include/nonstd/type.hpp) [![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://bintray.com/martinmoene/nonstd-lite/type-lite%3Anonstd-lite/_latestVersion) [![Try it on wandbox](https://img.shields.io/badge/on-wandbox-blue.svg)](https://wandbox.org/permlink/k1O8GhWYMyuZ6BcH) [![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](https://godbolt.org/z/ojNNN6)

**Contents**  
- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Synopsis](#synopsis)
- [Reported to work with](#reported-to-work-with)
- [Building the tests](#building-the-tests)
- [Other implementations of strong types](#other-implementations-of-strong-types)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)


Example usage
-------------

```C++
#include "nonstd/type.hpp"

typedef nonstd::ordered<int, struct day_tag , nonstd::no_default_t> Day;
typedef nonstd::ordered<int, struct year_tag, nonstd::no_default_t> Year;

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
```

### Compile and run
```
prompt> g++ -Wall -std=c++11 -I../include -o 01-basic 01-basic.cpp && ./01-basic 
```

In a nutshell
---------------
**type lite** provides building blocks to create strong types with, such as `bits`, `numeric`, `quantity` and `address`. 

**Features and properties of type** are ease of installation (single header), freedom of dependencies other than the standard library.


License
-------
*type lite* is distributed under the [Boost Software License](LICENSE.txt).
 

Dependencies
------------
*type lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).


Installation
------------
*type lite* is a single-file header-only library. Here are some ways to use it:

- As copied header in the [include](include) folder of the project source tree or somewhere reachable from your project.
- [As copied header used from CMake](doc/install.md#cmake-library)
- [As external Git project](doc/install.md#git-external)
- [As CMake package](doc/install.md#cmake-package)
- [As Conan package](doc/install.md#conan-package)


Synopsis
--------

**Contents**  
- [Namespace and types](#syn-types)
- [Create a default-constructible type](#syn-default-type)
- [Create a non-default-constructible type](#syn-non-default-type)
- [Create a sub-type](syn-sub-type)
- [Define a function taking a `type`-derived type](#syn-function)
- [Table with types, their operations and free functions and macros](#syn-table)

<a id="syn-types"></a>
### Namespace and types

Types and functions of *type lite* are in namespace `nonstd`.

With the exception of `boolean`, types `type` `bits`, `logical`, `equality`, `ordered`, `numeric`, `quantity`, `address`, `offset` are declared as:
```
template< typename T, typename Tag, typename D = T >
struct type;
```

With `boolean` declared as:

```
template< typename Tag, typename D = bool >
struct boolean;
```

Type `type` is the (possibly indirect) base class of the other strong types.  

<a id="syn-default-type"></a>
### Create a default-constructible type

Declaring default-constructible type Quantity:
```
typedef nonstd::quantity<double, struct QuantityTag> Quantity;
```

Using the macro:
```
type_DEFINE_TYPE_DEFAULT( Quantity, quantity, double )
```

<a id="syn-non-default-type"></a>
### Create a non-default-constructible type

Declaring non-default-constructible type Quantity:
```
typedef nonstd::quantity<double, struct QuantityTag, nonstd::no_default_t> Quantity;
```

Using the macro:
```
type_DEFINE_TYPE( Quantity, quantity, double )
```

<a id="syn-sub-type"></a>
### Create a sub-type

To enable the creation of operations that are common to different types, *type lite* allows to create sub types.
```
type_DEFINE_SUBTYPE(        QuantityA, Quantity)
type_DEFINE_SUBTYPE_DEFAULT(QuantityB, Quantity)
```

<a id="syn-function"></a>
### Define a function taking a `type`-derived type

```C++
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
```
Compile and run:
```
g++ -Wall -std=c++98 -I../include -o 05-function 05-function.cpp && 05-function.exe
7
```

<a id="syn-table"></a>
### Table with types, their operations and free functions and macros

| Kind                  | Std   | Operations / remarks |                                       
|-----------------------|-------|----------------------|
| **Types**             |&nbsp; | &nbsp; |
| type                  |&nbsp; | no operations; base class of the following types |
| bits                  |&nbsp; | ~&ensp;&amp;&ensp;&brvbar;&ensp;^&ensp;<<&ensp;>>&ensp;&amp;=&ensp;&brvbar;=&ensp;^=&ensp;<<=&ensp;>>= |
| boolean               |&nbsp; | explicit bool conversion, see [note 1](#note1) |
| logical               |&nbsp; | !&ensp;&amp;&amp;&ensp;&brvbar;&brvbar; |
| equality              |&nbsp; | ==&ensp;!= |
| ordered               |&nbsp; | equality&ensp;<&ensp;<=&ensp;>=&ensp;> |
| numeric               |&nbsp; | ordered&ensp;unary+&ensp;unary-&ensp;++&ensp;--&ensp;+&ensp;-&ensp;*&ensp;/&ensp;%&ensp;+=&ensp;-=&ensp;*=&ensp;/=&ensp;%= |
| quantity              |&nbsp; | ordered&ensp;unary+&ensp;unary-&ensp;+&ensp;-&ensp;*&ensp;/&ensp;+=&ensp;-=&ensp;*=&ensp;/=<br>with&ensp;q&thinsp;/&thinsp;q &rarr; T&ensp;T&thinsp;&times;&thinsp;q&ensp;q&thinsp;&times;&thinsp;T&ensp;q&thinsp;/&thinsp;T |
| offset                |&nbsp; | ordered&ensp;o&thinsp;+&thinsp;o&ensp;o&thinsp;-&thinsp;o&ensp;o&thinsp;+=&thinsp;o&ensp;o&thinsp;-=&thinsp;o  |
| address               |&nbsp; | ordered&ensp;a&thinsp;+&thinsp;o&ensp;a&thinsp;-&thinsp;o&ensp;a&thinsp;+=&thinsp;o&ensp;a&thinsp;-=&thinsp;o&ensp;o&thinsp;+&thinsp;a&ensp; |
| &nbsp;                |&nbsp; | &nbsp; |
| no_default_t          |&nbsp; | used to make type non-default-constructible|
| &nbsp;                |&nbsp; | &nbsp; |
| std::hash&lt;type&lt;...>>    | C++11  | hash type for `type` in namespace `std`; see `make_hash()` |
| &nbsp;                |&nbsp; | &nbsp; |
| **Free functions**    |&nbsp; | &nbsp; |
| make_hash()           |C++11  | create hash value for an object of strong type |
| swap()                |&nbsp; | swap two strong type objects |
| to_value()            |&nbsp; | convert strong type object to underlying value |
| [operator<<]          |&nbsp; | [not provided] |
| &nbsp;                |&nbsp; | &nbsp; |
| **Macros**            |&nbsp; | &nbsp; |
| type_DEFINE_TYPE            |&nbsp; | Define a strong type `S`, using tag `Tag` and implementation type `T` |
| type_DEFINE_TYPE_DEFAULT    |&nbsp; | Define a default-constructible strong type |
| type_DEFINE_SUBTYPE         |&nbsp; | Define a subtype `U` of a strong type `S` |
| type_DEFINE_SUBTYPE_DEFAULT |&nbsp; | Define a default-constructible subtype of a strong type |
| type_DEFINE_FUNCTION        |&nbsp; | Adapt an existing function `f` for a strong type `S` |
| type_DEFINE_FUNCTION_CE     |&nbsp; | Adapt an existing constexpr function `f` for a strong type `S` |

<a id="note1"></a>Note 1: On Windows, completely specify `nonstd::boolean` to prevent clashing with `boolean` from Windows SDK rpcndr.h
 

Configuration
-------------
There are no configuration flags currently.


Building the tests
------------------
To build the tests you need:

- [CMake](http://cmake.org), version 3.0 or later to be installed and in your PATH.
- A [suitable compiler](#reported-to-work-with).

The [*lest* test framework](https://github.com/martinmoene/lest) is included in the [test folder](test).

The following steps assume that the [*type lite* source code](https://github.com/martinmoene/type) has been cloned into a directory named `./type`.

1. Create a directory for the build outputs.

        cd ./type
        md build && cd build

2. Configure CMake to use the compiler of your choice (run `cmake --help` for a list).

        cmake -G "Unix Makefiles" -DTYPE_OPT_BUILD_TESTS=ON ..

3. Build the test suite.    

        cmake --build .

4. Run the test suite.    

        ctest -V

All tests should pass, indicating your platform is supported and you are ready to use *type lite*.


Other implementations of strong types
-------------------------------------
- Tony van Eerd. [StrongId](https://github.com/tvaneerd/code) on GitHub, since 2017.
- Jonathan Boccara. [NamedType](https://github.com/joboccara/NamedType) on GitHub, since 2017.
- Jonathan Müller. [type_safe](https://github.com/foonathan/type_safe) on GitHub, since 2016.
- Vicente J. Botet Escriba. [std-make strong](https://github.com/viboes/std-make/tree/master/include/experimental/fundamental/v3/strong) on GitHub since 2017.
- Martin Moene. [WholeValue](https://github.com/martinmoene/WholeValue) on GitHub, since 2012.
- Boost.Serialization. [Boost Strong Typedef](http://www.boost.org/doc/libs/1_61_0/libs/serialization/doc/strong_typedef.html). Boost 1.61.0. 


Notes and references
--------------------
*Blogs*
- Jonathan Boccara. [Strong types for strong interfaces](https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/). 8 December 2016.
- Jonathan Müller. [Tutorial: Emulating strong/opaque typedefs in C++](http://foonathan.net/blog/2016/10/19/strong-typedefs.html). 19 Oct 2016.
- Andrzej Krzemieński. [Declaring the move constructor](https://akrzemi1.wordpress.com/2015/09/11/declaring-the-move-constructor/). 11 September 2015.  
- Andrzej Krzemieński. [noexcept — what for?](https://akrzemi1.wordpress.com/2014/04/24/noexcept-what-for/). 24 April 2014.

*Presentations*
- Björn Fahller. [Type Safe C++? - LOL! :-)](https://github.com/ACCUConf/ACCUConf_PDFs/blob/master/2018/Bjorn_Fahller_-_Type_safe_c%2B%2B.pdf). ACCU 2018.
- Jonathan Boccara. [Strong types for strong interfaces](https://youtu.be/WVleZqzTw2k).  Meeting C++ 2017.
- Kyle Markley. [Extreme Type Safety with Opaque Typedefs](https://github.com/CppCon/CppCon2015/blob/master/Lightning%20Talks%20and%20Lunch%20Sessions/Extreme%20Type%20Safety%20with%20Opaque%20Typedefs/Extreme%20Type%20Safety%20with%20Opaque%20Typedefs%20-%20Kyle%20Markley%20-%20CppCon%202015.pdf). CppCon 2015.

*Proposals*
- Walter E. Brown. [N3515 - Toward Opaque Typedefs for C++1Y, v2](https://wg21.link/n3741). 30 August 2013.


Appendix
--------

### A.1 Compile-time information

The version of *type lite* is available via tag `[.version]`. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

### A.2 Type lite test specification

```
type: Disallows to default-construct a type thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)
type: Allows to default-construct a type thus defined
type: Allows to copy-construct a type from its underlying type
type: Allows to move-construct a type from its underlying type (C++11)
type: Allows to copy-construct a type
type: Allows to move-construct a type (C++11)
type: Allows to copy-assign a type
type: Allows to move-assign a type (C++11)
type: Allows to copy-swap a type
type: Allows to move-swap a type (C++11)
type: Allows to obtain hash of a type object (C++11)
boolean: Disallows to default-construct a boolean thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)
boolean: Disallows to substitute booleans with different tags (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)
boolean: Allows to default-construct a boolean thus defined
boolean: Allows to copy-construct a boolean from its underlying type
boolean: Allows explicit conversion to a native bool
boolean: Allows to negate a boolean
boolean: Allows to compare a boolean for equality
boolean: Allows to obtain hash of a boolean object (C++11)
logical: Disallows to default-construct a logical thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)
logical: Allows to default-construct a logical thus defined
logical: Allows to copy-construct a logical from its underlying type
logical: Allows to move-construct a logical from its underlying type (C++11)
logical: Allows to negate a logical
logical: Allows to and two logicals
logical: Allows to or two logicals
logical: Allows to obtain hash of a logical object (C++11)
equality: Disallows to default-construct an equality thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)
equality: Allows to default-construct an equality thus defined
equality: Allows to copy-construct an equality from its underlying type
equality: Allows to move-construct an equality from its underlying type (C++11)
equality: Allows to compare an equality for equality
equality: Allows to obtain hash of an equality object (C++11)
bits: Disallows to default-construct a bits thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)
bits: Allows to default-construct a bits thus defined
bits: Allows to copy-construct a bits from its underlying type
bits: Allows to move-construct a bits from its underlying type (C++11)
bits: Allows to compare bits for equality
bits: Allows to negate bits
bits: Allows to and bits
bits: Allows to or bits
bits: Allows to xor bits
bits: Allows to shift-left bits
bits: Allows to shift-right bits
bits: Allows to obtain hash of a bits object (C++11)
ordered: Disallows to default-construct an ordered thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)
ordered: Allows to default-construct an ordered thus defined
ordered: Allows to copy-construct an ordered from its underlying type
ordered: Allows to move-construct an ordered from its underlying type (C++11)
ordered: Allows to compare an ordered for equality
ordered: Allows to compare an ordered for order
ordered: Allows to obtain hash of an ordered object (C++11)
numeric: Disallows to default-construct a numeric thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)
numeric: Allows to default-construct a numeric thus defined
numeric: Allows to copy-construct a numeric from its underlying type
numeric: Allows to move-construct a numeric from its underlying type (C++11)
numeric: Allows to compare a numeric for equality
numeric: Allows to compare a numeric for order
numeric: Allows to apply unary+, unary-
numeric: Allows to apply pre- and post-increment and -decrement
numeric: Allows to add, subtract, multiply, divide, rest-divide numerics (x op y)
numeric: Allows to add, subtract, multiply, divide, rest-divide numerics (x op= y)
numeric: Allows to obtain hash of a numeric object (C++11)
quantity: Disallows to default-construct a quantity thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)
quantity: Allows to default-construct a quantity thus defined
quantity: Allows to copy-construct a quantity from its underlying type
quantity: Allows to move-construct a quantity from its underlying type (C++11)
quantity: Allows to compare a numeric for equality
quantity: Allows to compare a numeric for order
quantity: Allows to apply unary+, unary-
quantity: Allows to add, subtract quantities (x op y)
quantity: Allows to add, subtract quantities (x op= y)
quantity: Disallows to multiply a quantity with a quantity
quantity: Allows to multiply a quantity with a scalar (result: quantity)
quantity: Allows to divide a quantity by a scalar (result: quantity)
quantity: Allows to divide a quantity by a quantity (result: scalar)
quantity: Allows to obtain hash of a quantity object (C++11)
address: Disallows to default-construct an address thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)
address: Allows to default-construct an address thus defined
address: Allows to copy-construct an address from its underlying type
address: Allows to move-construct an address from its underlying type (C++11)
address: Disallows to add addresses
address: Allows to subtract addresses to yield an offset (a - a)
address: Allows to add, subtract an offset (a + o, a - o)
address: Allows to add, subtract an offset (a += o, a -= o)
address: Allows to an offset and an addresses (a + o, o + a)
address: Allows to subtract an offset from an address (a - o)
address: Disallows to subtract an addresses from an offset
address: Allows to obtain hash of an address object (C++11)
offset: Disallows to default-construct an offset thus defined (define type_CONFIG_CONFIRMS_COMPILATION_ERRORS)
offset: Allows to default-construct an offset thus defined
offset: Allows to copy-construct an offset from its underlying type
offset: Allows to move-construct an offset from its underlying type (C++11)
offset: Allows to add, subtract offsets (x op y)
offset: Allows to add, subtract offsets (x op= y)
offset: Allows to obtain hash of an offset object (C++11)
```
