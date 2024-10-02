cmake_minimum_required(VERSION 3.7)

project(WoollyBreakout)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(WoollyBreakout game.cpp main.cpp)
target_include_directories(WoollyBreakout PUBLIC game.h)
target_link_libraries(WoollyBreakout ${SDL2_LIBRARIES})
