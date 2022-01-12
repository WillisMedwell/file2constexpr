# The minimum cmake version requirements
cmake_minimum_required(VERSION 3.5)

# The project name
project(file2constexpr)

# set the C++ standard to C++ 20
set(CMAKE_CXX_STANDARD 23)

# Link all cpp files from /src to the variable "SOURCE"
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/include/ReadInput.hpp
    ${PROJECT_SOURCE_DIR}/include/WriteHeader.hpp
    ${PROJECT_SOURCE_DIR}/include/DirectoryHelper.hpp
    ${PROJECT_SOURCE_DIR}/include/CmdResponses.hpp
)

# Create the solution for project from the SOURCES variable
add_executable(file2constexpr ${SOURCES})

# The directories included in the build command
target_include_directories(file2constexpr
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Make the start up project file2constexpr
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT file2constexpr)

# TODO: Add tests and install targets if needed.
