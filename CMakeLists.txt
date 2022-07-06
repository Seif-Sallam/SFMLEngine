cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(CPM)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

CPMAddPackage(
    NAME SFML
    GIT_REPOSITORY git@github.com:Seif-Sallam/SFML.git
    GIT_TAG 2.5.x
)

CPMAddPackage(
    NAME box2d
    GIT_REPOSITORY git@github.com:Seif-Sallam/box2d.git
    GIT_TAG main
)

project(SFMLEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Thirdparty/imgui)
include_directories(AFTER Thirdparty/imgui/)
add_subdirectory(SFMLEngine)
include_directories(AFTER SFMLEngine/headers/)
add_subdirectory(Sandbox)
add_subdirectory(MazeGenerator)
add_subdirectory(Astroids)