#application

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/painter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/defaultscene.cpp
    
    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/painter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/defaultscene.h
    
    PARENT_SCOPE
)
