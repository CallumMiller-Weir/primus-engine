# CMakeList.txt
cmake_minimum_required (VERSION 3.8)

project ("primus-engine")

# package-management
file(GLOB primus_engine__package CONFIGURE_DEPENDS 
  "src/package/package.h" 
  "src/package/package.cpp" 
  "src/package/repository.h" 
  "src/package/repository.cpp"
)

# utility
file(GLOB primus_engine__utility CONFIGURE_DEPENDS 
  "src/utility/format.h" 
  "src/utility/format.cpp"
  "src/utility/logger.h" 
  "src/utility/logger.cpp"
)

add_executable (primus-engine 
  "src/main.cpp"
  ${primus_engine__package}
  ${primus_engine__utility}
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