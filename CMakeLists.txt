cmake_minimum_required(VERSION 3.10)

project(robot_garden LANGUAGES C)

find_package(SDL2 REQUIRED)

add_executable(robot_garden src/main.c)

target_include_directories(robot_garden PRIVATE 
  include/
)

target_compile_options(robot_garden PRIVATE
  -Wall
  -Wextra
  -Wconversion
  -Werror
  -pedantic
  -fopt-info
  -g
)

add_custom_target(
  clang-tidy-check clang-tidy -p ${CMAKE_BINARY_DIR}/compile_commands.json -checks=cert* ${sources}
  DEPENDS ${sources}
)

target_link_libraries(robot_garden
  -lm
  SDL2::SDL2
)
