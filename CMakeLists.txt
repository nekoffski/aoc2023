cmake_minimum_required(VERSION 3.10)
project(aoc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSPDLOG_COMPILED_LIB=1)

set(libs fmt kc spdlog)
set(targets 1 2 3 4 5 6)

add_subdirectory(libkc)

foreach (target ${targets})
    add_executable(${target} solutions/${target}.cpp)
    target_link_libraries(${target} ${libs})
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
