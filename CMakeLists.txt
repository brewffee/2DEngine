cmake_minimum_required(VERSION 3.31.6)
set(CMAKE_CXX_STANDARD 26)

# Project information
project(2DEngine VERSION 1.0.0 LANGUAGES CXX)

# Local files
file(GLOB_RECURSE sources "src/*.cpp")
file(GLOB_RECURSE headers "include/2DEngine/*.h")
file(GLOB_RECURSE inline "include/2DEngine/*.inl")

# Local dependencies
add_subdirectory(vendor)
include_directories(vendor/include)
set(LOCAL_LIBS glad)

# System dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(
    include
    ${OPENGL_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIR}
)

# Executable
add_executable(2DEngine main.cpp ${headers} ${sources} ${inline})
target_link_libraries(2DEngine
    SDL3_image glfw
    ${LOCAL_LIBS}
    ${OPENGL_LIBRARIES}
    ${GLFW3_LIBRARIES}
)
