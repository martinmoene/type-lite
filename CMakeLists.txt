# Copyright (C) 2018 Martin Moene.
#
# This code is licensed under the MIT License (MIT).

cmake_minimum_required( VERSION 3.0 )

project( type )

include( GNUInstallDirs )

add_library( type INTERFACE )

enable_testing()

add_subdirectory( test )
#add_subdirectory( example )

install( DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

# end of file
