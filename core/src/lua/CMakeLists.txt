#manager

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/resourcemanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/guimanager.cpp
    
    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/resourcemanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/guimanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/luawrapper.h
    
    PARENT_SCOPE
) 
