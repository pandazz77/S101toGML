project(libS101)

# Collect libS101 sources
file(GLOB SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)
set(LIBS101_HEADERS ${HDRS} PARENT_SCOPE)

add_library(${PROJECT_NAME} ${SRCS} ${LIBS101_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})