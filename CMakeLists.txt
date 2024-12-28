cmake_minimum_required(VERSION 3.10)

# Project name and version
project(CanonicalTest VERSION 1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Include vcpkg toolchain file
if(WIN32 OR  WIN64)
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "Path to vcpkg toolchain")
endif()

# Find CURL package (vcpkg handles platform-specific installations)
find_package(CURL REQUIRED)

# Create the executable
add_executable(CanonicalTest src/main.cpp src/ubuntu_image_fetcher.cpp)

# Link CURL to the executable
target_link_libraries(CanonicalTest PRIVATE CURL::libcurl)

# Include directories explicitly for CanonicalTest
target_include_directories(CanonicalTest PRIVATE 
    src 
    ${CMAKE_SOURCE_DIR}/external/nlhomann_json/include
)

# Cross-platform CMake configuration
if (WIN32)
    message(STATUS "Building on Windows")
elseif (APPLE)
    message(STATUS "Building on macOS")
elseif (UNIX)
    message(STATUS "Building on Linux")
endif()
