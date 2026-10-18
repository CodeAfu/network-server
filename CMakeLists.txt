cmake_minimum_required(VERSION 3.20)
project(network-server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(network-server ${SOURCES})
target_compile_options(network-server PRIVATE -Wall -Wextra -ggdb)
target_include_directories(network-server PRIVATE include)
