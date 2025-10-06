project(libS101)

# Collect libS101 sources
file(GLOB SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(GLOB SRCS_GML
    ${CMAKE_CURRENT_SOURCE_DIR}/S101GML/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/S101GML/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/S101GML/*.hpp
)
include_directories(S101GML)

add_library(${PROJECT_NAME} STATIC ${SRCS} ${HDRS} ${SRCS_GML})
target_link_libraries(${PROJECT_NAME} pugixml clipper)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/S101GML)