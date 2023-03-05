cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME spdlog)

Include(FetchContent)
if (NOT ${LIBRARY_NAME}_FIND_QUIETLY)
    set(FETCHCONTENT_QUIET OFF)
endif ()

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT ${LIBRARY_NAME}_FOUND)
    FetchContent_Declare(
            ${LIBRARY_NAME}
            URL https://github.com/gabime/spdlog/archive/refs/tags/v1.11.0.zip
    )
    FetchContent_MakeAvailable(${LIBRARY_NAME})
    FetchContent_GetProperties(${LIBRARY_NAME})
    message(STATUS "${LIBRARY_NAME} is available now")
endif ()