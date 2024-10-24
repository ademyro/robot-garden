cmake_minimum_required(VERSION 3.10)

project(robot_garden LANGUAGES C)

find_package(SDL2 REQUIRED)

add_executable(robot_garden src/main.c)

target_link_libraries(robot_garden SDL2::SDL2)
