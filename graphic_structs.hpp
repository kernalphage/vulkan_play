#ifndef VULKAN_PLAY_GRAPHIC_STRUCTS_HPP
#define VULKAN_PLAY_GRAPHIC_STRUCTS_HPP

//
// Created by matt on 1/8/18.
//

#include <glm/glm.hpp>
#include <vector>

struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int presentFamily = -1;
    bool isComplete() { return graphicsFamily >= 0 && presentFamily >= 0; }
};

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription = {};

        return bindingDescription;
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

#endif //VULKAN_PLAY_GRAPHIC_STRUCTS_HPP
