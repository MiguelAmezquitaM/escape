cmake_minimum_required(VERSION 3.25)

project(escape)

add_executable(
    # name
    escape

    # files
    src/main.cpp
    src/window.cpp
)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)
add_subdirectory(lib/glm)

target_link_libraries(escape PRIVATE glfw glad glm)
