#core

cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#сделать подобные фихи для поддерживаемых систем
if(${CMAKE_SYSTEM} MATCHES "Linux")
    # Linux specific code
    if(${CMAKE_SYSTEM} MATCHES "i686")
        set(OperatingSystem "Linux i686")
        message("DETECTED ${OperatingSystem}")
        set(ALLEGRO_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x86/allegro5)
        set(LUA_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x86/lua52)
        set(FREETYPE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x86/freetype)
    endif()
    if(${CMAKE_SYSTEM} MATCHES "x86_64")
        set(OperatingSystem "Linux x86_64")
        message("DETECTED ${OperatingSystem}")
        set(ALLEGRO_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x64/allegro5)
        set(LUA_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x64/lua52)
        set(FREETYPE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x64/freetype)
    endif()

    set(ALLEGRO_LIBRARIES
        m
        pthread
        X11
        Xext
        Xcursor
        Xinerama
        Xrandr
        GL
        GLU
    )
    set(ALLEGRO_LIBS
        ${ALLEGRO_LIB_DIR}/liballegro-static.a
        ${ALLEGRO_LIBRARIES}
    )

    set(LUA_LIBS
        ${LUA_LIB_DIR}/liblua.a
    )

    set(FREETYPE_LIBS
        ${FREETYPE_LIB_DIR}/libfreetype.a
    )
endif()

set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/conf/core.conf)

add_subdirectory(src)
add_subdirectory(test)






