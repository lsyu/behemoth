# labs4physics

cmake_minimum_required(VERSION 2.8.0)

include_directories(../../include/)

add_subdirectory(layers)


add_executable(labs4physics ${SRCS} ${HEADERS} main.cpp)
target_link_libraries(labs4physics
    engine_core
)

file(COPY gui DESTINATION  ${CMAKE_BINARY_DIR}/bin/res)
file(COPY core.conf DESTINATION  ${CMAKE_BINARY_DIR}/bin)

