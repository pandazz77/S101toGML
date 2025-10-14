project(S101toGML)

set(SRCS
    S101toGML.cpp S101toGML.h
)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} libS101 S101GML)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    COMPONENT ${PROJECT_NAME}
)