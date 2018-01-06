cmake_minimum_required(VERSION 3.4)
project(vulkan_play)
set(VULKAN_SDK_PATH $ENV{VULKAN_SDK_PATH})
set(Vulkan_INCLUDE_DIR "${VULKAN_SDK_PATH}/include")
set(Vulkan_LIB_DIR "${VULKAN_SDK_PATH}/lib")

include_directories(${Vulkan_INCLUDE_DIR})
set(LIBRARIES "vulkan")
link_directories(${Vulkan_LIB_DIR})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g")
set(SOURCE_FILES main.cpp)

add_executable(vulkan_play ${SOURCE_FILES})
target_link_libraries(vulkan_play glfw ${GLFW_LIBRARIES})
target_link_libraries(vulkan_play ${LIBRARIES})

# shaders! https://gist.github.com/vlsh/a0d191701cb48f157b05be7f74d79396

set(GLSL_VALIDATOR "${VULKAN_SDK_PATH}/bin/glslangValidator")
file(GLOB_RECURSE GLSL_SOURCE_FILES
        "shaders/*.frag"
        "shaders/*.vert"
        )

foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
    add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
            COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
            DEPENDS ${GLSL})
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
        Shaders
        DEPENDS ${SPIRV_BINARY_FILES}
)

add_dependencies(vulkan_play Shaders)

add_custom_command(TARGET vulkan_play POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:vulkan_play>/shaders/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/shaders"
        "$<TARGET_FILE_DIR:vulkan_play>/shaders"
        )
