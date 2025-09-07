cmake_minimum_required(VERSION 3.31)
project(robot_garden_prototype C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add GLFW
add_subdirectory(external/glfw)

# GLAD
add_library(glad external/glad/src/gl.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(robot_garden_prototype src/main.c src/shader/shader.c
        src/render/render.c
        src/texture/texture.c
        src/shader/loader.c
        src/file/file.c
        src/log/log.c
        src/chunk/chunk.c
        src/garden/tile.c)

target_compile_options(robot_garden_prototype PRIVATE -g)
target_link_libraries(robot_garden_prototype glfw glad GL dl m)
target_include_directories(robot_garden_prototype PUBLIC external external/glad/include include)
