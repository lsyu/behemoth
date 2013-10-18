# src

cmake_minimum_required(VERSION 2.8.8)

include_directories(../../include)

add_subdirectory(algorithm)
add_subdirectory(application)
add_subdirectory(factory)
add_subdirectory(glm)
add_subdirectory(gli)
add_subdirectory(object)
add_subdirectory(openglstuff)
add_subdirectory(manager)

add_subdirectory(glsl)
add_subdirectory(scripts)

set(CORE_SRCS
    ${CORE_SRCS}
    main.cpp
    constants.h
)

add_definitions(-Wall -Wextra -pedantic -Weffc++ -Woverloaded-virtual -Wold-style-cast -Wconversion -Wsign-conversion -std=c++11)
add_executable(hello_world ${CORE_SRCS} ${CORE_HEADERS})
target_link_libraries(hello_world
    ${LOG_LIBS}
    ${ALLEGRO_LIBS}
    ${LUA_LIBS}
)

add_custom_target(TEST_TARGET ALL DEPENDS)
add_custom_command(TARGET TEST_TARGET
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/res/shaders
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/scripts
)

foreach( FILE_I ${GLSL_FILES})
add_custom_command(TARGET TEST_TARGET
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${FILE_I} ${CMAKE_BINARY_DIR}/bin/res/shaders
)
endforeach(FILE_I)

foreach( FILE_I ${SCRIPT_FILES})
add_custom_command(TARGET TEST_TARGET
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${FILE_I} ${CMAKE_BINARY_DIR}/bin/scripts
)
endforeach(FILE_I)

add_custom_command(TARGET TEST_TARGET
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CONF_FILE} ${CMAKE_BINARY_DIR}/bin
)

