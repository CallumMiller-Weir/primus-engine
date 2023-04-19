# CMakeList.txt
cmake_minimum_required (VERSION 3.8)

project ("primus-engine")

# Add source to this project's executable.
add_executable (primus-engine 
  src/main.cpp
)

# GLFW setup
set (GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set (GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory (dependencies/glfw)

# Dependencies
target_link_libraries (primus-engine 
  glfw 
)