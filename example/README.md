# Skaldi example

This is a simple example of how to use Skaldi.

## Installation

In order to use the Skaldi library, you first need to obtain the package by using the **findSkaldi.cmake** file.

This can be done by following the code in **findSkaldi.cmake** file:

**findSkaldi.cmake**
```cmake
cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME Skaldi)

Include(FetchContent)
if (NOT ${LIBRARY_NAME}_FIND_QUIETLY)
    set(FETCHCONTENT_QUIET OFF)
endif ()

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT ${LIBRARY_NAME}_FOUND)
    set(SKALDI_INCLUDE_LIBRARIES ${${LIBRARY_NAME}_FIND_COMPONENTS}) # enabled libraries
    set(SKALDI_ENABLE_CMAKE ON) # CMake support
    message(STATUS "Fetching Skaldi")
    FetchContent_Declare(
            ${LIBRARY_NAME}
            URL https://github.com/Fazanwolf/Skaldi/zipball/main
    )
    FetchContent_MakeAvailable(${LIBRARY_NAME})
    FetchContent_GetProperties(${LIBRARY_NAME})
endif ()
```

After obtaining the package, you can use it by adding the following code to your **CMakeLists.txt** file:

```cmake
find_package(Skaldi 0.0.1.0 REQUIRED)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            Skaldi
)
```

This will allow you to link the Skaldi library to your project and use its functionalities.

## Example

The example is a simple server and client that can be used to test the library.

### Usage

The usage of the example is as follows:

```bash
USAGE
./test [flag]
-h, --help      Display this help message.
-v, --version   Display the version of the library.
./test base type [ip] port
base            The base network that you want, server or client.
type            The type of socket connection, TCP or UDP.
[ip]            The target ip, needed only for client base.
port            The port to use."

EXAMPLES
./test server udp 5000"               
./test client udp 0.0.0.0 5000"       
./test server tcp 5001"               
./test client tcp 0.0.0.0 5001

Skaldi is a library free of use by anyone and developped by Fazanwolf.\
```

## Contributors

* [Fazanwolf](https://github.com/Fazanwolf)

## License

[MIT](../LICENSE)