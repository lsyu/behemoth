cmake_minimum_required(VERSION 2.8.0)

project(labs4physics)

add_subdirectory(core)

file(COPY res DESTINATION  ${CMAKE_BINARY_DIR}/bin)
