# FINAL PROJECT CMakeList
 
cmake_minimum_required(VERSION 3.22) # Specify CMake version.

project(FinalProject
   )     # Define project name

set(CMAKE_CXX_STANDARD 17) # Specify C++ version.
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")  
message(STATUS "CMakeLists.txt is at ${PROJECT_SOURCE_DIR}") # To print something.


# Dependencies - get openGL ready for use
find_package(OpenGL REQUIRED)

# Specify the paths for third-party libraries (GLEW, GLFW)
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


# include all of the source files (the first argument is the project name)
 add_executable(FinalProject 
 main.cpp
Asteroid.h
Spacecraft.h
game.h
ErrorLog.h
)


# Link libraries (OpenGL, GLEW, GLFW)
target_link_libraries(${CMAKE_PROJECT_NAME} OpenGL::GL glfw)

target_link_libraries(${CMAKE_PROJECT_NAME} ${GLEW_STATIC_LIBRARIES})

target_link_libraries(${CMAKE_PROJECT_NAME} "${PROJECT_SOURCE_DIR}/third_party/freeglut/lib/x64/freeglut.lib")

target_link_libraries(${CMAKE_PROJECT_NAME} "${PROJECT_SOURCE_DIR}/third_party/glew/install/lib/libglew32d.lib")
target_link_libraries(${CMAKE_PROJECT_NAME} "${PROJECT_SOURCE_DIR}/third_party/glew/install/lib/glew32d.lib")
