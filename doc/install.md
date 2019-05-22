Installation of *type lite* 
===========================

**Contents**  
- [As copied header used from CMake](#cmake-library)
- [As external Git project](#git-external)
- [As CMake package](#cmake-package)
- [As Conan package](#conan-package)


<a id="cmake-library"></a>
As copied header used from CMake
--------------------------------

Put a copy of [`type-lite.hpp`](include/type-lite.hpp) located in folder [include](include) directly into the project source tree or somewhere reachable from your project, for example in *project-root*/include. A minimal CMake setup using this header might look as follows.

In project root folder:

```CMake
cmake_minimum_required( VERSION 3.5 FATAL_ERROR )

project( use-type-lite LANGUAGES CXX )

# Provide #include access to type-lite as 'nonstd/type.hpp': 

set( TYPE_LITE_INCLUDE_DIR include )  # adapt as necessary
add_library( type INTERFACE )
target_include_directories( type INTERFACE ${TYPE_LITE_INCLUDE_DIR} )

# Build program from src:

add_subdirectory( src ) 
```

In folder src:

```CMake
cmake_minimum_required( VERSION 3.5 FATAL_ERROR )

project( program-using-type-lite LANGUAGES CXX )

# Make program executable:

set( SOURCES main.cpp)
add_executable( program ${SOURCES} )
target_link_libraries( program PRIVATE type )
```


<a id="git-external"></a>
As external Git project
-----------------------

Another approach is to automatically fetch the entire *type-lite* repository from github and configure it as an external project.

```CMake
cmake_minimum_required( VERSION 3.5 FATAL_ERROR )

project( use-type-lite LANGUAGES CXX )

# Set default ExternalProject root directory and add type-lite:

set( TYPE_LITE_URL https://github.com/martinmoene/type-lite.git )

include( ExternalProject )
find_package( Git REQUIRED )

set_directory_properties( PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/3rd_party )

ExternalProject_Add(
    type-extern
    GIT_REPOSITORY ${TYPE_LITE_URL}
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
   )

# Provide #include access to type-lite as 'nonstd/type.hpp': 

ExternalProject_Get_Property( type-extern SOURCE_DIR )
set( TYPE_LITE_INCLUDE_DIR ${SOURCE_DIR}/include CACHE INTERNAL "Include folder for type-lite")

add_library( type INTERFACE )
target_include_directories( type INTERFACE ${TYPE_LITE_INCLUDE_DIR} )

# Build program from src:

add_subdirectory( src ) 
```

In folder src:
```CMake
cmake_minimum_required( VERSION 3.5 FATAL_ERROR )

project( program-using-type-lite LANGUAGES CXX )

# Make program executable:

set( SOURCES main.cpp)
add_executable( program ${SOURCES} )
target_link_libraries( program PRIVATE type )
```

This setup brings in more than you need, but also makes it easy to update *type-lite* to the latest version.
<!--See [example/cmake-extern](example/cmake-extern) for a complete example.-->


<a id="cmake-package"></a>
As CMake package
----------------

1. First install the *type-lite* CMake package from its source, for example:

		cd ./type-lite
		cmake -H. -B../_build -G"Unix Makefiles" -DCMAKE_INSTALL_PREFIX="~/dev"
		cmake --build ../_build --target install

	<!--See also [script/install-type-pkg.py](script/install-type-pkg.py) that can perform these steps for you. It also lets you control compiler and build configuration.-->

2. Next, you can use the *type-lite* CMake package, for example:

	```CMake
	cmake_minimum_required( VERSION 3.5 FATAL_ERROR )
	
	find_package( type-lite "1.2" REQUIRED )
	
	project( program-using-type-lite LANGUAGES CXX )
	
	add_executable(        program main.cpp )
	target_link_libraries( program PRIVATE nonstd::type-lite )
	```
	Configure and build:

		cd ./type-lite/example/cmake-pkg
		cmake -H. -B../_build -G"Unix Makefiles" -DCMAKE_INSTALL_PREFIX=_stage -DCMAKE_PREFIX_PATH="~/dev"
		cmake --build ../_build

	<!--See [example/cmake-pkg/Readme.md](example/cmake-pkg/Readme.md) for a complete example.-->


<a id="conan-package"></a>
As Conan package
----------------

For the [conan package manager](https://www.conan.io/), follow these steps:

1. Add *nonstd-lite* to the conan remotes:

        conan remote add nonstd-lite https://api.bintray.com/conan/martinmoene/nonstd-lite

2. Add a reference to *type-lite* to the *requires* section of your project's `conanfile.txt` file:

        [requires]
        type-lite 1.2.3@nonstd-lite/stable

3. Run conan's install command:

        conan install

