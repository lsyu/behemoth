# opengl stuff

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexbufferobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexarrayobject.cpp
    
    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexbufferobject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexarrayobject.h

    PARENT_SCOPE
)
