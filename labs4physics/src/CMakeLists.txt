# labs4physics

cmake_minimum_required(VERSION 2.8.0)

include_directories(../../include/)

set(SRCS
    main.cpp
)

add_executable(labs4physics ${SRCS})
target_link_libraries(labs4physics
    engine_core
)

file(COPY gui DESTINATION  ${CMAKE_BINARY_DIR}/bin)
file(COPY core.conf DESTINATION  ${CMAKE_BINARY_DIR}/bin)

