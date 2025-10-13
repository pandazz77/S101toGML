project(S101GML)

file(GLOB SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)
set(S101GML_HEADERS ${HDRS} PARENT_SCOPE)

add_library(${PROJECT_NAME} ${SRCS} ${S101GML_HEADERS})
target_link_libraries(${PROJECT_NAME} libS101 pugixml)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})