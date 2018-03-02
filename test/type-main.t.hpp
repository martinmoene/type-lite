// Copyright (c) 2018 Martin Moene
//
// https://github.com/martinmoene/type
//
// This code is licensed under the MIT License (MIT).

#pragma once

#ifndef TEST_TYPE_HPP_INCLUDED
#define TEST_TYPE_HPP_INCLUDED

#include "type.hpp"

// Limit C++ Core Guidelines checking to GSL Lite:

#if defined(_MSC_VER) && _MSC_VER >= 1910
# include <CppCoreCheck/Warnings.h>
# pragma warning(disable: ALL_CPPCORECHECK_WARNINGS)
#endif

#include "lest_cpp03.hpp"

using namespace nonstd;

#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

namespace lest {

using ::nonstd::operator<<;

} // namespace lest

#endif // TEST_TYPE_HPP_INCLUDED

// end of file
