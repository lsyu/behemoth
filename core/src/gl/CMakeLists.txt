# opengl

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexbufferobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexarrayobject.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/shaderfactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/texturefactory.cpp
    
    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexbufferobject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexarrayobject.h

    ${CMAKE_CURRENT_SOURCE_DIR}/shaderfactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/texturefactory.h

    PARENT_SCOPE
)
