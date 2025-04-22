cmake_minimum_required(VERSION 3.31.6)
project(2d)

set(CMAKE_CXX_STANDARD 26)

find_package(OpenGL REQUIRED)
find_package(SDL3 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

include_directories(2d
    ${SDL3_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${Vulkan_INCLUDE_DIR}
    ${GLFW3_INCLUDE_DIR}
)

# just use a glob lol
file(GLOB_RECURSE sources "src/*.cpp")
file(GLOB_RECURSE headers "include/*.h")

add_executable(2d main.cpp
    ${headers} ${sources}
)

target_link_libraries(2d
    SDL3::SDL3
    SDL3_image
    glfw
    ${OPENGL_LIBRARIES}
    ${Vulkan_LIBRARY}
    ${GLFW3_LIBRARIES}
)
