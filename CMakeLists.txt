cmake_minimum_required(VERSION 3.16)
project(S101toGML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Enable shared libraries in Release mode
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(BUILD_SHARED_LIBS ON)
    
    # Set output directory for Release builds
    set(RELEASE_OUTPUT ${CMAKE_BINARY_DIR}/release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RELEASE_OUTPUT})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RELEASE_OUTPUT})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RELEASE_OUTPUT})
    
    # Create include directory in release build
    set(INCLUDE_OUTPUT_DIRECTORY ${RELEASE_OUTPUT}/include)
    file(MAKE_DIRECTORY ${INCLUDE_OUTPUT_DIRECTORY})
    
    # Create subdirectories for each library
    file(MAKE_DIRECTORY ${INCLUDE_OUTPUT_DIRECTORY}/libS101)
    file(MAKE_DIRECTORY ${INCLUDE_OUTPUT_DIRECTORY}/S101GML)
    file(MAKE_DIRECTORY ${INCLUDE_OUTPUT_DIRECTORY}/pugixml)
endif()

add_subdirectory(extlibs/pugixml)

add_subdirectory(libS101)
add_subdirectory(S101GML)
add_subdirectory(S101toGML)

# Copy header files to include directory after build in Release mode
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Copy only header files to the include directory
    add_custom_target(copy_headers ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIBS101_HEADERS} ${RELEASE_OUTPUT}/include/libS101
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${S101GML_HEADERS} ${RELEASE_OUTPUT}/include/S101GML
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PUGIXML_HEADERS} ${RELEASE_OUTPUT}/include/pugixml
        COMMENT "Copying header files to release include directory"
        VERBATIM
    )
endif()
