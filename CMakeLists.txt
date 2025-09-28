cmake_minimum_required(VERSION 3.11) # FetchContent requires at least 3.11
project(Mumbeling_Mages C)

# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master # Or a specific version tag like 5.0
)

FetchContent_MakeAvailable(raylib)

set(SOURCES
    src/main.c
    src/enemy/enemy.c
    src/enemy/enemy_properties.c
    src/enemy/enemy_texture.c
    src/player/player.c
    src/player/player_properties.c
    src/player/player_texture.c
    src/core/bullet.c
    src/core/game.c
    src/core/powerup.c
    src/core/orb.c
    src/core/window.c
    src/core/map.c
    src/core/IO_handler.c
    src/core/animation_handler.c
    src/core/resource_tracker.c
    src/core/camera.c
    src/mumble/mumble.c
    src/mumble/mumble_properties.c
)

add_executable(game src/main.c ${SOURCES})

target_include_directories(game PRIVATE includes)

# The target_link_libraries command will now automatically use the fetched raylib
target_link_libraries(game PRIVATE raylib m)

add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:game>/assets
)

