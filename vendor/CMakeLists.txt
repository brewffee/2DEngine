cmake_minimum_required(VERSION 3.31.6)
project(glad VERSION 2.0.8 LANGUAGES C)

include_directories(include)

# Dependency setup
add_library(glad STATIC src/gl.c)
