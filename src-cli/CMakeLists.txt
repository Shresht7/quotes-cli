cmake_minimum_required(VERSION 3.10)

# Set the project name
project(quotes VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(quotes main.cpp quotes.cpp helpers.cpp)

# Include directories
target_include_directories(quotes PUBLIC "${PROJECT_SOURCE_DIR}/src")
