cmake_minimum_required(VERSION 3.25)

project(escape)

add_executable(
    # name
    escape

    # files
    src/main.cpp
    # src/window.cpp
    src/game/sys/render_system.cpp
    src/game/sys/window_system.cpp
    src/game/sys/drag_system.cpp
    src/game/sys/collider_system.cpp
    src/game/sys/input_system.cpp
)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)
add_subdirectory(lib/glm)

target_link_libraries(escape PRIVATE glfw glad glm)
target_compile_options(escape PRIVATE -std=c++20 -Wall -O3 -Werror -Wpedantic --pedantic-errors -Wconversion)
