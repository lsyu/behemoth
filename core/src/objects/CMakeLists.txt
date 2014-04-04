# object

add_subdirectory(gui)
add_subdirectory(3d)

set(CORE_SRCS ${CORE_SRCS} PARENT_SCOPE )
set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractentity.h
    PARENT_SCOPE
)

