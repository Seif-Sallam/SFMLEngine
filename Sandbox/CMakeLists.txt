cmake_minimum_required(VERSION 3.16)

FILE(GLOB_RECURSE SOURCES ./src/*.cpp)
FILE(GLOB_RECURSE HEADERS ./src/*.h)

add_executable(SandBox
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(
    SandBox
    PRIVATE
    ./headers/
)

target_link_libraries(SandBox
    PRIVATE
    SFMLEngine
    sfmlimgui
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(SandBox
        PRIVATE
        RSC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
    )
else()
    target_compile_definitions(SandBox
        PRIVATE
        RSC_DIR="./SandBox_rsc"
    )

    add_custom_command(
        TARGET SandBox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/rsc
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/SandBox_rsc
    )
endif()