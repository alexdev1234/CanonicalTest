cmake_minimum_required(VERSION 3.10)

# Project name and version
project(CanonicalTest VERSION 1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Include vcpkg toolchain file (

# Executable
add_executable(CanonicalTest src/main.cpp src/ubuntu_image_fetcher.cpp)

# Include directories
target_include_directories(CanonicalTest PRIVATE src)

# Libcurl
if(WIN32)
	set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "Path to vcpkg toolchain")
endif()

find_package(CURL REQUIRED)
target_link_libraries(CanonicalTest PRIVATE CURL::libcurl)

#nlohmann/json
target_include_directories(CanonicalTest PRIVATE external/nlohmann_json/include/nlohmann)

# Cross-platform CMake configuration
if (WIN32)
    message(STATUS "Building on Windows")
elseif (APPLE)
    message(STATUS "Building on macOS")
elseif (UNIX)
    message(STATUS "Building on Linux")
endif()