#object

set(CORE_SRCS
    ${CORE_SRCS}

    ${CMAKE_CURRENT_SOURCE_DIR}/basic2dentity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangletext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rectanglesymbol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/font.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/textbuffer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/light.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
    
    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractentity.h
    ${CMAKE_CURRENT_SOURCE_DIR}/basic2dentity.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangletext.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rectanglesymbol.h
    ${CMAKE_CURRENT_SOURCE_DIR}/font.h
    ${CMAKE_CURRENT_SOURCE_DIR}/textbuffer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/light.h
    ${CMAKE_CURRENT_SOURCE_DIR}/camera.h
    
    PARENT_SCOPE
) 
 
