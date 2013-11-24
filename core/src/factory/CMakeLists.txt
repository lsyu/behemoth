# factory

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/shaderfactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fontfactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/texturefactory.cpp

    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/shaderfactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/fontfactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/texturefactory.h

    PARENT_SCOPE
)
