cmake_minimum_required(VERSION 3.10)

# Set the project name
project(quotes VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Libraries
include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.2 # Replace with the latest version as needed
)

FetchContent_MakeAvailable(json)

# Add the executable
add_executable(quotes main.cpp quotes.cpp helpers.cpp ansi.cpp)

# Link the nlohmann_json library to the quotes target
target_link_libraries(quotes PRIVATE nlohmann_json::nlohmann_json)

# Include directories
target_include_directories(quotes PUBLIC "${PROJECT_SOURCE_DIR}/src")
