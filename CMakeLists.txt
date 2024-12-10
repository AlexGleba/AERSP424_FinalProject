cmake_minimum_required(VERSION 3.22) # Specify CMake version.
project( Final Project
   ) # A project name. This can be anything.

set(CMAKE_CXX_STANDARD 17) # Specify C++ version.
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic -Wextra")
message(STATUS "CMakeLists.txt is at ${PROJECT_SOURCE_DIR}") # To print something.

include(CTest)
enable_testing()

# Dependencies
find_package(OpenGL REQUIRED)

# Specify the paths for third-party libraries (GLEW, GLFW, Matplot++)
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/glew/install")
find_package(GLEW REQUIRED)

list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/glfw/install")
find_package(glfw3 REQUIRED)

list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/matplotplusplus/install")
find_package(Matplot++ REQUIRED)

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
# The second argument is the source files (main.cpp).
//add_executable(Final_Project 
//main.cpp
#Asteroid.h
#Spacecraft.h
#Game.h
#ErrorLog.h
)
// add_executable(${PROJECT_NAME} src/main.cpp)

add_executable(Final Project ${SOURCE_FILES})


# Link libraries (OpenGL, GLEW, GLFW, Matplot++)
target_link_libraries(${CMAKE_PROJECT_NAME} OpenGL::GL glfw libglew_static Matplot++::matplot)

# Enable packaging
set(CMAKE_INSTALL_PREFIX .)
install(FILES ${SOURCE_FILES} DESTINATION . PERMISSIONS OWNER_READ OWNER_WRITE WORLD_READ WORLD_EXECUTE COMPONENT deb)

set(CPACK_PROJECT_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${CMAKE_PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_SOURCE_IGNORE_FILES
    /.git
    /dist
    /results
    /.*build.*
    /\\\\.DS_Store
)
set(CPACK_ARCHIVE_COMPONENT_INSTALL 1)
include(CPack)
