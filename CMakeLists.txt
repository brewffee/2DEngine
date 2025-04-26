cmake_minimum_required(VERSION 3.31.6)
set(CMAKE_CXX_STANDARD 26)

# Project information
project(2DEngine VERSION 1.0.0 LANGUAGES CXX)

file(GLOB_RECURSE sources "src/*.cpp")
file(GLOB_RECURSE headers "include/*.h")
file(GLOB_RECURSE inline "include/*.inl")

# Dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${Vulkan_INCLUDE_DIR}
    ${GLFW3_INCLUDE_DIR}
)

# Executable
add_executable(2DEngine main.cpp ${headers} ${sources} ${inline})
target_link_libraries(2DEngine
    SDL3_image glfw
    ${OPENGL_LIBRARIES}
    ${Vulkan_LIBRARY}
    ${GLFW3_LIBRARIES}
)
