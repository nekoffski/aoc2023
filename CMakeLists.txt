cmake_minimum_required(VERSION 3.10)
project(aoc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSPDLOG_COMPILED_LIB=1)

set(libs fmt kc spdlog)
file(GLOB solutions ${CMAKE_CURRENT_SOURCE_DIR}/solutions/*.cpp)

add_subdirectory(libkc)

foreach (solution ${solutions})
    get_filename_component(target ${solution} NAME_WE)
    add_executable(${target} ${solution})
    target_link_libraries(${target} ${libs})
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
