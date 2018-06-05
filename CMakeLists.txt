# Copyright 2018 by Martin Moene
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.0 )

project( type )

include( GNUInstallDirs )

add_library( type INTERFACE )

enable_testing()

add_subdirectory( test )
#add_subdirectory( example )

install( DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

# end of file
