# CMakeList

cmake_minimum_required(VERSION 3.23) # Specify the version of CMake
project(Final_Project) # The project name can be titled anything
set(CMAKE_CXX_STANDARD 20) # Specify C++ version.

# Accessing CMake variables can be done using ${VARIABLE_NAME}.
message(STATUS "CMakeLists.txt is at ${PROJECT_SOURCE_DIR}") # Print

# Including a directory where header files are typically stored.
# CMAKE_SOURCE_DIR is another variable that CMake automatically created, which is a path to the folder location where CMakeList.txt is stored.
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create a binary file.
# First argument is the name of the binary file, whic is set to be the project name.
# The other arguments are source files.
# Header files are not needed in the add_executable() portion since they are assumed to be included in the source files.
add_executable(Final_Project 
    main.cpp
    Asteroid.h
    Spacecraft.h
    Game.h
    # Additional .cpp files can be included if needed
)
