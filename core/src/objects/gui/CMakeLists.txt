# gui

set(CORE_SRCS
    ${CORE_SRCS}

    ${CMAKE_CURRENT_SOURCE_DIR}/basic2dentity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangletext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rectanglesymbol.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/entity2dfactory.cpp

    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/basic2dentity.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangletext.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rectanglesymbol.h

    ${CMAKE_CURRENT_SOURCE_DIR}/entity2dfactory.h

    PARENT_SCOPE
)

