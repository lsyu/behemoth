# light
set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/basiclight.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/directionlight.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pointlight.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lightfactory.cpp

    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractlight.h
    ${CMAKE_CURRENT_SOURCE_DIR}/basiclight.h
    ${CMAKE_CURRENT_SOURCE_DIR}/directionlight.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pointlight.h
    ${CMAKE_CURRENT_SOURCE_DIR}/lightfactory.h

    PARENT_SCOPE
)
