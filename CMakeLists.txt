# Copyright 2018 by Martin Moene
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.5 )

# type version, updated by script/update-version.py:

set( type_version "0.0.0" )

# At default, enable building and performing of tests and building of examples:

option( TYPE_OPT_BUILD_TESTS    "Build and perform type tests" ON )
option( TYPE_OPT_BUILD_EXAMPLES "Build type examples" OFF )

project( type LANGUAGES CXX )

include( GNUInstallDirs )

set( package_name "type" )

# Interface library:

add_library(                
    ${package_name} INTERFACE )
    
target_include_directories( 
    ${package_name} INTERFACE "$<BUILD_INTERFACE:${include_source_dir}>" )

# Installation:

install( 
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

# If requested, build and perform tests, build examples:

enable_testing()

if ( TYPE_OPT_BUILD_TESTS )
    add_subdirectory( test )
endif()

if ( TYPE_OPT_BUILD_EXAMPLES )
    add_subdirectory( example )
endif()

# end of file
