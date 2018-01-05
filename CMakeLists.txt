cmake_minimum_required(VERSION 3.4)
project(vulkan_play)

find_package(Vulkan)
add_subdirectory("/home/matt/git/glfw/" "refs/glfw")
include_directories("/home/git/glfw/include/")

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

add_executable(vulkan_play ${SOURCE_FILES})
target_link_libraries(vulkan_play glfw ${GLFW_LIBRARIES})
if (Vulkan_FOUND)
  include_directories(${Vulkan_INCLUDE_DIRS})
  target_link_libraries (vulkan_play ${Vulkan_LIBRARIES})
endif (Vulkan_FOUND)
