cmake_minimum_required(VERSION 3.21.0)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)

project(Vulkan VERSION 1.0 LANGUAGES CXX)

add_executable(App main.cpp app.cpp window.cpp instance.cpp layerExtensions.cpp device.cpp)

target_link_libraries(App glfw vulkan dl pthread X11 Xrandr Xi)

