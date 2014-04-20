add_subdirectory(entity)
add_subdirectory(node)

set(CORE_SRCS
    ${CORE_SRCS}
    #${CMAKE_CURRENT_SOURCE_DIR}/object3d.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/objectfactory.cpp

    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    #${CMAKE_CURRENT_SOURCE_DIR}/object3d.h
    #${CMAKE_CURRENT_SOURCE_DIR}/objectfactory.h

    PARENT_SCOPE
)
