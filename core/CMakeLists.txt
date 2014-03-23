#engine_core

project(behemoth)
cmake_minimum_required(VERSION 2.8.0)

add_definitions(-DGL_GLEXT_PROTOTYPES)

#сделать подобные фихи для поддерживаемых систем
if(${CMAKE_SYSTEM} MATCHES "Linux")
    # Linux specific code
    if(${CMAKE_SYSTEM} MATCHES "i686")
        set(OperatingSystem "Linux i686")
        message("DETECTED ${OperatingSystem}")
        set(FREEGLUT_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x86/freeglut)
        set(LUA_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x86/lua52)
        set(FREETYPE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x86/freetype)
    endif()
    if(${CMAKE_SYSTEM} MATCHES "x86_64")
        set(OperatingSystem "Linux x86_64")
        message("DETECTED ${OperatingSystem}")
        set(FREEGLUT_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x64/freeglut)
        set(LUA_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x64/lua52)
        set(FREETYPE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/x64/freetype)
    endif()

    set(FREEGLUT_LIBS
        ${FREEGLUT_LIB_DIR}/libglut.a
        GL
        X11
        Xext
        Xcursor
        Xinerama
        Xrandr
        Xxf86vm
        Xi
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






