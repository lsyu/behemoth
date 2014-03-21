# 3d

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/basiccamera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/perspectivecamera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/orthocamera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camerafactory.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/basiclight.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/directionlight.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pointlight.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lightfactory.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/basic3dentity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entityfactory.cpp

    
    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractcamera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/basiccamera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/perspectivecamera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/orthocamera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/camerafactory.h

    ${CMAKE_CURRENT_SOURCE_DIR}/abstractlight.h
    ${CMAKE_CURRENT_SOURCE_DIR}/basiclight.h
    ${CMAKE_CURRENT_SOURCE_DIR}/directionlight.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pointlight.h
    ${CMAKE_CURRENT_SOURCE_DIR}/lightfactory.h

    ${CMAKE_CURRENT_SOURCE_DIR}/basic3dentity.h
    ${CMAKE_CURRENT_SOURCE_DIR}/entityfactory.cpp
    
    PARENT_SCOPE
)
