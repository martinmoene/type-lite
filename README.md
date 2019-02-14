# type: A tiny single-file header-only library for strong types for C++98, C++11 and later 

[![Language](https://img.shields.io/badge/C%2B%2B-98/11/14/17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://travis-ci.org/martinmoene/type.svg?branch=master)](https://travis-ci.org/martinmoene/type) [![Build status](https://ci.appveyor.com/api/projects/status/1ha3wnxtam547m8p?svg=true)](https://ci.appveyor.com/project/martinmoene/type) [![Version](https://badge.fury.io/gh/martinmoene%2Ftype.svg)](https://github.com/martinmoene/type/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://github.com/martinmoene/type/blob/master/include/nonstd/type.hpp) [![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://bintray.com/martinmoene/nonstd-lite/type-lite%3Anonstd-lite/_latestVersion) [![Try it on wandbox](https://img.shields.io/badge/on-wandbox-blue.svg)](https://wandbox.org/permlink/pGGPF1Sp3vdCpJXe) [![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](http://bit.ly/mm-type-godbolt)

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

typedef nonstd::numeric<int, struct day_tag , nonstd::no_default_t> Day;
typedef nonstd::numeric<int, struct year_tag, nonstd::no_default_t> Year;

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
**type** ...

**Features and properties of type** are ease of installation (single header), freedom of dependencies other than the standard library. ...


License
-------
*type* is distributed under the [Boost Software License](LICENSE.txt).
 

Dependencies
------------
*type* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).


Installation
------------
*type* is a single-file header-only library. Put `type.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.


Synopsis
--------

**Contents**  

| Kind                  | Std   | Operations |                                       
|-----------------------|-------|--------------------|
| **Types**             |&nbsp; | . |
| type                  |&nbsp; | none |
| bits                  |&nbsp; | &amp;, &brvbar;, ^, <<, >>, &amp;=, &brvbar;=, ^=, <<=, >>= |
| boolean               |&nbsp; | explicit bool conversion, see [note 1](#note1) |
| logical               |&nbsp; | ~, &amp;&amp;, &brvbar;&brvbar; |
| equality              |&nbsp; | ==, != |
| ordered               |&nbsp; | < <= >= > |
| numeric               |&nbsp; | unary +, unary -, ++, --, +, -, *, /, %, +=, -=, *=, /=, %= |
| quantity              |&nbsp; | as numeric, but with q / q &rarr; T, T &times; q, q &times; T, q / T |
| offset                |&nbsp; | as ordered, o + o, o - o |
| address               |&nbsp; | as ordered, a + o, o + a, a - o  |
| &nbsp;                |&nbsp; | &nbsp; |
| **Free functions**    |&nbsp; | . |
| abs                   |&nbsp; | &nbsp; |
| swap                  |&nbsp; | &nbsp; |
| operator<<            |&nbsp; | &nbsp; |
| &nbsp;                |&nbsp; | &nbsp; |
| **Macros**            |&nbsp; | . |
| type_DEFINE_TYPE |&nbsp; | . |
| type_DEFINE_TYPE_DEFAULT |&nbsp; | . |
| type_DEFINE_SUBTYPE |&nbsp; | . |
| type_DEFINE_SUBTYPE_DEFAULT |&nbsp; | . |
| type_DEFINE_FUNCTION |&nbsp; | &nbsp; |

<a id="note1"></a>Note 1: On Windows, ...(completely specify)... `nonstd::boolean` to prevent clashing with `boolean` from Windows SDK rpcndr.h

### Defining a function taking a `type`-derived type

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
 

Configuration
-------------


Building the tests
------------------
To build the tests you need:

- [CMake](http://cmake.org), version 3.0 or later to be installed and in your PATH.
- A [suitable compiler](#reported-to-work-with).

The [*lest* test framework](https://github.com/martinmoene/lest) is included in the [test folder](test).

The following steps assume that the [*type* source code](https://github.com/martinmoene/type) has been cloned into a directory named `./type`.

1. Create a directory for the build outputs.

        cd ./type
        md build && cd build

2. Configure CMake to use the compiler of your choice (run `cmake --help` for a list).

        cmake -G "Unix Makefiles" -DTYPE_OPT_BUILD_TESTS=ON ..

3. Build the test suite.    

        cmake --build .

4. Run the test suite.    

        ctest -V

All tests should pass, indicating your platform is supported and you are ready to use *type*.


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
```
