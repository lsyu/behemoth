#application

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractscene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/defaultscene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractevent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/eventmouseclick.cpp
    
    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractscene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/defaultscene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractevent.h
    ${CMAKE_CURRENT_SOURCE_DIR}/eventmouseclick.h
    
    PARENT_SCOPE
)
