cmake_minimum_required(VERSION 3.16)

FILE(GLOB_RECURSE SOURCES ./src/*.cpp)
FILE(GLOB_RECURSE HEADERS ./src/*.h)

add_executable(MazeGenerator
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(
    MazeGenerator
    PRIVATE
    ./headers/
)

target_link_libraries(MazeGenerator
    PRIVATE
    SFMLEngine
    sfmlimgui
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(MazeGenerator
        PRIVATE
        RSC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
    )
else()
    target_compile_definitions(MazeGenerator
        PRIVATE
        RSC_DIR="./MazeGenerators_rsc"
    )

    add_custom_command(
        TARGET MazeGenerator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/rsc
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/MazeGenerator_rsc
    )
endif()