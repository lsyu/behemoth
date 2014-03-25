# labs4physics

cmake_minimum_required(VERSION 2.8.0)

include_directories(../../include/)

add_executable(example_messagebox ${SRCS} ${HEADERS} example_messagebox.cpp)
target_link_libraries(example_messagebox behemoth)

add_executable(example_cube_with_label ${SRCS} ${HEADERS} example_cube_with_label.cpp)
target_link_libraries(example_cube_with_label behemoth)

file(COPY gui DESTINATION  ${CMAKE_BINARY_DIR}/bin/res)
file(COPY core.conf DESTINATION  ${CMAKE_BINARY_DIR}/bin)

