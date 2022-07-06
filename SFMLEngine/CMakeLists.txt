cmake_minimum_required(VERSION 3.16)

FILE(GLOB_RECURSE SOURCES ./src/*.cpp)
FILE(GLOB_RECURSE HEADERS ./src/*.h)

add_library(
    SFMLEngine
    STATIC
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(SFMLEngine
    PUBLIC
    GL
    sfmlimgui
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    box2d
)
target_include_directories(SFMLEngine
    PRIVATE
    headers/
)

target_compile_definitions(SFMLEngine
    PRIVATE
    RSC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
)