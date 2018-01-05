cmake_minimum_required(VERSION 3.4)
project(vulkan_play)
set(VULKAN_SDK_PATH "/home/matt/projects/VulkanSDK/1.0.65.0/x86_64")
set(Vulkan_INCLUDE_DIR "${VULKAN_SDK_PATH}/include")
set(Vulkan_LIB_DIR "${VULKAN_SDK_PATH}/lib")

include_directories(${Vulkan_INCLUDE_DIR})
set(LIBRARIES "vulkan")
link_directories(${Vulkan_LIB_DIR})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)

add_executable(vulkan_play ${SOURCE_FILES})
target_link_libraries(vulkan_play glfw ${GLFW_LIBRARIES})
target_link_libraries(vulkan_play ${LIBRARIES})
