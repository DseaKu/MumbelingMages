cmake_minimum_required(VERSION 3.10)
project(Mumbeling_Mages C)

# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib CONFIG REQUIRED)

set(SOURCES
src/bullet.c
src/enemy/enemy.c
src/enemy/enemy_properties.c
src/game.c
src/main.c
src/player.c
src/powerup.c
src/orb.c
src/window.c
src/map.c
src/IO_handler.c
src/animation_handler.c
src/resource_tracker.c
src/mage_properties.c
src/camera.c
)

add_executable(game src/main.c ${SOURCES})

target_include_directories(game PRIVATE includes)

target_link_libraries(game PRIVATE raylib m)

add_custom_command(TARGET game POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/assets
  $<TARGET_FILE_DIR:game>/assets
)

