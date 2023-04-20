# CMakeList.txt
cmake_minimum_required (VERSION 3.8)

project ("primus-engine")

# add source to this project's executable
file(GLOB primus_engine__src CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable (primus-engine 
  ${primus_engine__src}
)

# glfw setup
set (GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set (GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory (dependencies/glfw)

# json setup
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(dependencies/json)

# Dependencies
target_link_libraries (primus-engine 
  glfw
  nlohmann_json::nlohmann_json
)