#application

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/eventmouseclick.cpp

    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractevent.h
    ${CMAKE_CURRENT_SOURCE_DIR}/eventmouseclick.h

    PARENT_SCOPE
)
