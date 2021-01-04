
cmake_minimum_required(
    VERSION 3.4
    )

project(
    liuyunbin-toys
    )

set(
    CXX_FLAGS
    -Wall
    -Werror
    -Wextra
    -Wno-unused-parameter
    -std=c++11
    )

string(
    REPLACE
    ";"
    " "
    CMAKE_CXX_FLAGS
    "${CXX_FLAGS}"
    )

set(
    CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/lib
    )

set(
    CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/lib
    )

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/bin
    )

add_subdirectory(
    cpp-standard-library
    )

add_subdirectory(
    huge-number
    )

add_subdirectory(
    linux-commands
    )

add_subdirectory(
    linux-games
    )

add_subdirectory(
    linux-network-program
    )

