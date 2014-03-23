# src of engine_core

cmake_minimum_required(VERSION 2.8.0)

include_directories(
    glm                 # for glm and gli
    ../../include/ft2   # for freetype
    ../../include       # for other includes
)

add_subdirectory(application)
add_subdirectory(events)
add_subdirectory(fonts)
add_subdirectory(objects)
add_subdirectory(gl)
add_subdirectory(glm/glm)
add_subdirectory(gli/gli)
add_subdirectory(lua)

add_library(behemoth SHARED ${CORE_SRCS} ${CORE_HEADERS})
target_link_libraries(behemoth
    ${FREEGLUT_LIBS}
    ${LUA_LIBS}
    ${FREETYPE_LIBS}
)
