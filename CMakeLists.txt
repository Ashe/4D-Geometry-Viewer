cmake_minimum_required(VERSION 3.7)
project(App)

# Export compilation commands to JSON file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Messages to check everything is working
message("Using CMake version ${CMAKE_VERSION}")
message("Processing CMakeLists.txt")

# Compiler version
set(CMAKE_CXX_STANDARD 17)

# Add dependencies to project
add_subdirectory("deps")

# Prepare to add all files to project
file(GLOB_RECURSE SOURCEFILES
  "src/*.h"
  "src/*.cpp"
)

# Create the executable
set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} src/main.cpp)

# Add source files
target_sources(${EXECUTABLE_NAME} PUBLIC
  ${SOURCEFILES})

# Add libraries to the project
target_link_libraries(${PROJECT_NAME} PUBLIC
  glfw
  glad
  glbinding::glbinding
  glm
  imgui)
