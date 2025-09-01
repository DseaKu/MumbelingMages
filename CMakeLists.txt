cmake_minimum_required(VERSION 3.10)
project(Mumbeling_Mages C)

# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib CONFIG REQUIRED)

set(SOURCES
src/core/bullet.c
src/enemy/enemy.c
src/enemy/enemy_properties.c
src/enemy/enemy_texture.c
src/core/game.c
src/main.c
src/core/player.c
src/core/powerup.c
src/core/orb.c
src/core/window.c
src/core/map.c
src/core/IO_handler.c
src/core/animation_handler.c
src/core/resource_tracker.c
src/mage/mage_properties.c
src/mage/mage_texture.c
src/core/camera.c
)

add_executable(game src/main.c ${SOURCES})

target_include_directories(game PRIVATE includes)

target_link_libraries(game PRIVATE raylib m)

add_custom_command(TARGET game POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/assets
  $<TARGET_FILE_DIR:game>/assets
)

