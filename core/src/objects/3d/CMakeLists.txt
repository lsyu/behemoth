# 3d

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/basiccamera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/perspectivecamera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/orthocamera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camerafactory.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/light.cpp

    
    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractcamera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/basiccamera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/perspectivecamera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/orthocamera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/camerafactory.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/light.h
    
    PARENT_SCOPE
)
