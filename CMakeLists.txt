cmake_minimum_required(VERSION 3.22) # Specify CMake version.
project(FinalProject
   ) # A project name. This can be anything.

set(CMAKE_CXX_STANDARD 17) # Specify C++ version.
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")
message(STATUS "CMakeLists.txt is at ${PROJECT_SOURCE_DIR}") # To print something.

#include(CTest)
#enable_testing()

# Dependencies
find_package(OpenGL REQUIRED)

# Specify the paths for third-party libraries (GLEW, GLFW, Matplot++)
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/glew/install")
find_package(GLEW REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/glfw/install")
find_package(glfw3 REQUIRED)

set(GLFW_DIR "${PROJECT_SOURCE_DIR}/third_party/glfw/install")
include_directories("${GLFW_DIR}/include")
set(GLFW_STATIC_LIBRARIES "${GLFW_DIR}/lib/glfw3.lib")

include_directories(${PROJECT_SOURCE_DIR}/third_party/freeglut/include)


# Include directories for header files
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

# List the main source file (main.cpp)
set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/main.cpp  # Main entry point of the project
)

# Add other source files if needed, for example:
# list(APPEND SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/other_source_file.cpp)

# Create a binary file. 
# The first argument is the name of the binary file.
# The second argument is thshe source files (main.cpp).
 add_executable(FinalProject 
 main.cpp
Asteroid.h
Spacecraft.h
game.h
ErrorLog.h
)


# Link libraries (OpenGL, GLEW, GLFW, Matplot++)
target_link_libraries(${CMAKE_PROJECT_NAME} OpenGL::GL glfw libglew_static)

target_link_libraries(${CMAKE_PROJECT_NAME} ${GLEW_STATIC_LIBRARIES})

target_link_libraries(${CMAKE_PROJECT_NAME} "${PROJECT_SOURCE_DIR}/third_party/freeglut/lib/freeglut.lib")