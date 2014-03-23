cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(-Wall -pedantic -std=c++11)

add_subdirectory(core)
add_subdirectory(examples)

file(COPY res DESTINATION  ${CMAKE_BINARY_DIR}/bin)
