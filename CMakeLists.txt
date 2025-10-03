cmake_minimum_required(VERSION 3.16)
project(S101toGML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Add external libraries
add_library(clipper STATIC
    extlibs/Clipper/include/clipper.cpp
)
target_include_directories(clipper PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/Clipper/include
)

# Prefer system pugixml; fallback to fetching upstream
find_path(PUGIXML_INCLUDE_DIR pugixml.hpp)
find_library(PUGIXML_LIBRARY pugixml)
include(FetchContent)
if(NOT PUGIXML_INCLUDE_DIR OR NOT PUGIXML_LIBRARY)
    message(STATUS "pugixml not found on system; fetching upstream...")
    FetchContent_Declare(
      pugixml
      GIT_REPOSITORY https://github.com/zeux/pugixml.git
      GIT_TAG v1.14
    )
    FetchContent_MakeAvailable(pugixml)
endif()

# Compatibility layer for Linux (MFC/Win32 shims)
add_library(compat_mfc STATIC
    libS101/compat/compat_mfc.cpp
)
target_include_directories(compat_mfc PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libS101/compat
)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/libS101/compat
)
if(PUGIXML_INCLUDE_DIR)
    target_include_directories(libS101 PUBLIC ${PUGIXML_INCLUDE_DIR})
endif()

if(TARGET pugixml)
    target_link_libraries(libS101 PUBLIC clipper compat_mfc pugixml)
else()
    target_link_libraries(libS101 PUBLIC clipper compat_mfc ${PUGIXML_LIBRARY})
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


