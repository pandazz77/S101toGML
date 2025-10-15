project(pugixml)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(SRCS
    src/pugixml.cpp
)

set(PUGIXML_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pugixml.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pugiconfig.hpp
)

add_library(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC src)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "${PUGIXML_HEADERS}"
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY
        DESTINATION lib
    COMPONENT ${PROJECT_NAME}
    RUNTIME
        DESTINATION bin
    COMPONENT ${PROJECT_NAME}
    ARCHIVE
        DESTINATION lib
    COMPONENT ${PROJECT_NAME}
    PUBLIC_HEADER
        DESTINATION include/${PROJECT_NAME}
    COMPONENT ${PROJECT_NAME}
)