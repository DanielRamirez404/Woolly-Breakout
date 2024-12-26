cmake_minimum_required(VERSION 3.14)

project(Test)

include(FetchContent)

FetchContent_Declare(asio-cmake
  GIT_REPOSITORY https://github.com/kingsamchen/asio-cmake.git
  GIT_TAG        origin/master
)

# Specify asio version
set(ASIO_CMAKE_ASIO_TAG asio-1-12-2)
FetchContent_MakeAvailable(asio-cmake)
# ...

add_executable(Test main.cpp)

target_link_libraries(Test
  PRIVATE asio
)
