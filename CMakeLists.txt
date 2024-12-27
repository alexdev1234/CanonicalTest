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
target_include_directories(CanonicalTest PRIVATE external/libcurl/include)

# External dependencies
add_subdirectory(external/nlohmann_json)

# Link external libraries
target_link_libraries(CanonicalTest PRIVATE nlohmann_json::nlohmann_json)

if(WIN32)
    target_link_libraries(CanonicalTest PRIVATE external/libcurl/lib/libcurl.lib)
else()
    target_link_libraries(CanonicalTest PRIVATE external/libcurl/lib/libcurl.a)
endif()

# Tests
enable_testing()
add_executable(test_canonical tests/test_main.cpp)