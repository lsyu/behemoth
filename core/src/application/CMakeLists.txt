#application

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractlayer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/basicguilayer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractevent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/eventmouseclick.cpp
    
    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractlayer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/basicguilayer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractevent.h
    ${CMAKE_CURRENT_SOURCE_DIR}/eventmouseclick.h
    
    PARENT_SCOPE
)
