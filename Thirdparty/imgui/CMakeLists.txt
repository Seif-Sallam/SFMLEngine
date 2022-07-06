cmake_minimum_required(VERSION 3.16)

FILE(GLOB SOURCES ./*.cpp)
FILE(GLOB HEADERS ./*.h)

add_library(
    sfmlimgui
    STATIC
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(sfmlimgui
    PRIVATE
    GL
    sfml-graphics
    sfml-window
    sfml-system
)