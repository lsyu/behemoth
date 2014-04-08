# node
set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/basicnode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/nodefactory.cpp

    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/basicnode.h
    ${CMAKE_CURRENT_SOURCE_DIR}/nodefactory.h

    PARENT_SCOPE
)
