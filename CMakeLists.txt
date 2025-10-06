cmake_minimum_required(VERSION 3.16)
project(S101toGML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_subdirectory(extlibs/pugixml)
add_subdirectory(extlibs/Clipper)

# Collect libS101 sources
file(GLOB LIBS101_SOURCES
    libS101/*.cpp
)

# Exclude Visual Studio specific files if present
list(FILTER LIBS101_SOURCES EXCLUDE REGEX ".*libS101\\.vcxproj.*|.*pch\\.cpp$")

add_library(libS101 STATIC ${LIBS101_SOURCES})
target_include_directories(libS101 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libS101
    ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/Clipper/include
)
if(PUGIXML_INCLUDE_DIR)
    target_include_directories(libS101 PUBLIC ${PUGIXML_INCLUDE_DIR})
endif()

if(TARGET pugixml)
    target_link_libraries(libS101 PUBLIC clipper pugixml)
else()
    target_link_libraries(libS101 PUBLIC clipper ${PUGIXML_LIBRARY})
endif()

if(UNIX)
    target_compile_definitions(libS101 PUBLIC _LINUX)
endif()

# Executable
add_executable(S101toGML
    S101toGML/S101toGML.cpp
)
target_include_directories(S101toGML PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/S101toGML
    ${CMAKE_CURRENT_SOURCE_DIR}/libS101
)
if(TARGET pugixml)
    target_link_libraries(S101toGML PRIVATE libS101 pugixml)
else()
    target_link_libraries(S101toGML PRIVATE libS101 ${PUGIXML_LIBRARY})
endif()

if(UNIX)
    target_compile_definitions(S101toGML PRIVATE _LINUX)
endif()


