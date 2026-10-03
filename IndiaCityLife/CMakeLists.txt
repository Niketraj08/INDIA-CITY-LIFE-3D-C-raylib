cmake_minimum_required(VERSION 3.16)
project(IndiaCityLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib 5.0 QUIET)

if(NOT raylib_FOUND)
    message(WARNING "raylib was not found. Install raylib 5.x and configure CMAKE_PREFIX_PATH.")
endif()

add_executable(IndiaCityLife
    src/main.cpp
    src/Game.cpp
    src/World.cpp
    src/Player.cpp
    src/Vehicle.cpp
    src/NPC.cpp
    src/Traffic.cpp
    src/Weather.cpp
    src/Mission.cpp
)

target_include_directories(IndiaCityLife PRIVATE include)

if(raylib_FOUND)
    target_link_libraries(IndiaCityLife PRIVATE raylib)
endif()

if(WIN32)
    target_link_libraries(IndiaCityLife PRIVATE winmm gdi32)
endif()
