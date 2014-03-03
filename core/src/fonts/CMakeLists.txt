# font

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/font.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fontfactory.cpp

    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/font.h
    ${CMAKE_CURRENT_SOURCE_DIR}/fontfactory.h

    PARENT_SCOPE
)
