cmake_minimum_required(VERSION 3.16)

set(SOURCES
    ./src/Game.cpp
    ./src/LevelScene.cpp
    ./src/main.cpp
    ./src/Components/AsteroidController.cpp
    ./src/Components/AsteroidsCreator.cpp
    ./src/Components/BulletController.cpp
    ./src/Components/ExplosionController.cpp
    ./src/Components/PlayerController.cpp
    ./src/Prefabs/Asteroid.cpp
    ./src/Prefabs/Bullet.cpp
    ./src/Prefabs/Explosion.cpp
    ./src/Prefabs/SpaceShip.cpp
)

set(HEADERS
    ./headers/Game.h
    ./headers/LevelScene.h
    ./headers/Components/AsteroidController.h
    ./headers/Components/AsteroidsCreator.h
    ./headers/Components/BulletController.h
    ./headers/Components/ExplosionController.h
    ./headers/Components/PlayerController.h
    ./headers/Prefabs/Asteroid.h
    ./headers/Prefabs/Bullet.h
    ./headers/Prefabs/Explosion.h
    ./headers/Prefabs/SpaceShip.h
)

add_executable(Asteroids
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(
    Asteroids
    PRIVATE
    ./headers/
)

target_link_libraries(Asteroids
    PRIVATE
    SFMLEngine
    sfmlimgui
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(Asteroids
        PRIVATE
        RSC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
    )
else()
    target_compile_definitions(Asteroids
        PRIVATE
        RSC_DIR="./Asteroids_rsc"
    )

    add_custom_command(
        TARGET Asteroids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/rsc
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/Asteroids_rsc
    )
endif()