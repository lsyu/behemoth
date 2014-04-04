#manager

set(CORE_SRCS
    ${CORE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/basicluamanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/resourcemanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/guimanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene3dmanager.cpp

    PARENT_SCOPE
)

set(CORE_HEADERS
    ${CORE_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/basicluamanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/resourcemanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/guimanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/scene3dmanager.h


    ${CMAKE_CURRENT_SOURCE_DIR}/luawrapper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/abstracteventlistener.h

    PARENT_SCOPE
)
