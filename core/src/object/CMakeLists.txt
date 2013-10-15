#object

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/entity.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/material.cpp

#    ${CMAKE_CURRENT_SOURCE_DIR}/triangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangle.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/light.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
    
    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/entity.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/material.h

#    ${CMAKE_CURRENT_SOURCE_DIR}/triangle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangle.h

    ${CMAKE_CURRENT_SOURCE_DIR}/light.h
    ${CMAKE_CURRENT_SOURCE_DIR}/camera.h
    
    PARENT_SCOPE
) 
 
