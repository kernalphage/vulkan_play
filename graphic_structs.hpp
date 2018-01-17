#ifndef VULKAN_PLAY_GRAPHIC_STRUCTS_HPP
#define VULKAN_PLAY_GRAPHIC_STRUCTS_HPP

//
// Created by matt on 1/8/18.
//

#include <array>
#include <glm/glm.hpp>
#include <vector>
struct QueueFamilyIndices {
  int graphicsFamily = -1;
  int presentFamily = -1;
  bool isComplete() { return graphicsFamily >= 0 && presentFamily >= 0; }
};

struct BufferMemory{
  VkBuffer buffer;
  VkDeviceMemory bufferMemory;
};

struct UniformBufferObject {
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 proj;
};


struct Vertex {
  glm::vec2 pos;
  glm::vec3 color;

  static VkVertexInputBindingDescription getBindingDescription() {
    VkVertexInputBindingDescription bindingDescription = {};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
  }
  static std::array<VkVertexInputAttributeDescription, 2>
  getAttributeDescriptions() {
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset = offsetof(Vertex, pos);

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = offsetof(Vertex, color);
    return attributeDescriptions;
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

#endif // VULKAN_PLAY_GRAPHIC_STRUCTS_HPP
