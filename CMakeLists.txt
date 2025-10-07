cmake_minimum_required(VERSION 3.16)
project(S101toGML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


add_subdirectory(extlibs/pugixml)

add_subdirectory(libS101)
add_subdirectory(S101GML)
add_subdirectory(S101toGML)
