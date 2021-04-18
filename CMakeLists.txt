cmake_minimum_required(VERSION 3.17)
project(naval_battle C)

set(CMAKE_C_STANDARD 99)
include_directories(inc)
add_executable(naval_battle src/main.c src/game_initialization.c inc/struct.h src/display.c inc/display.h src/stdjm.c inc/stdjm.h src/boat.c inc/boat.h src/file.c inc/file.h src/player.c inc/player.h src/weapon.c inc/weapon.h)