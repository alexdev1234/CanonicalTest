cmake_minimum_required(VERSION 3.10)

# Project name and version
project(CanonicalTest VERSION 1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Executable
add_executable(CanonicalTest src/main.cpp src/ubuntu_image_fetcher.cpp)

# Include directories
target_include_directories(CanonicalTest PRIVATE src)

# External dependencies
add_subdirectory