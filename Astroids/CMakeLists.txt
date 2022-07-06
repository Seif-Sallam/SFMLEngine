cmake_minimum_required(VERSION 3.16)

FILE(GLOB_RECURSE SOURCES ./src/*.cpp)
FILE(GLOB_RECURSE HEADERS ./src/*.h)

add_executable(Astroids
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(
    Astroids
    PRIVATE
    ./headers/
)

target_link_libraries(Astroids
    PRIVATE
    SFMLEngine
    GL
    sfmlimgui
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

target_compile_definitions(Astroids
    PRIVATE
    RSC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
)