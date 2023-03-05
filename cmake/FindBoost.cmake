cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME Boost)

Include(FetchContent)
if (NOT ${LIBRARY_NAME}_FIND_QUIETLY)
    set(FETCHCONTENT_QUIET OFF)
endif ()

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT ${LIBRARY_NAME}_FOUND)
    set(BOOST_INCLUDE_LIBRARIES ${${LIBRARY_NAME}_FIND_COMPONENTS}) # enabled libraries
    set(BOOST_ENABLE_CMAKE ON) # CMake support
    message(STATUS "Fetching Boost")
    FetchContent_Declare(
            ${LIBRARY_NAME}
            URL https://github.com/boostorg/boost/releases/download/boost-1.81.0/boost-1.81.0.tar.xz
    )
    FetchContent_MakeAvailable(${LIBRARY_NAME})
    FetchContent_GetProperties(${LIBRARY_NAME})
endif ()