# 3d

add_subdirectory(object)
add_subdirectory(camera)
add_subdirectory(light)

set(CORE_SRCS ${CORE_SRCS} PARENT_SCOPE)
set(CORE_HEADERS ${CORE_HEADERS} PARENT_SCOPE)
