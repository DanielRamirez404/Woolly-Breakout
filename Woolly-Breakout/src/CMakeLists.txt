cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Wolly-Breakout VERSION 1.0)

add_executable(Wolly-Breakout main.cpp game.cpp)
target_include_directories(Wolly-Breakout PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


