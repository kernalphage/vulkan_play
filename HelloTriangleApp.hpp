//
// Created by matt on 1/13/18.
//

#ifndef VULKAN_PLAY_HELLOTRIANGLEAPP_HPP
#define VULKAN_PLAY_HELLOTRIANGLEAPP_HPP
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

#include "graphic_structs.hpp"

class HelloTriangleApp {
public:
  void run();

  static std::vector<char> readFile(const std::string &filename);

private:
  void initWindow();

  static void onWindowResized(GLFWwindow *window, int width, int height);

  void initVulkan();

  void createVertexBuffer();
  void createIndexBuffer();
  void createUniformBuffer();
  uint32_t findMemoryType(uint32_t typeFilter,
                          VkMemoryPropertyFlags properties);
  void recreateSwapChain();
  void createSemaphores();
  void createCommandBuffers();
  void createCommandPool();
  void createFramebuffers();
  void createRenderPass();
  void createDescriptorSetLayout();
  void createDescriptorSet();
  void createGraphicsPipeline();

  VkShaderModule createShaderModule(const std::vector<char> &code);
  void createImageViews();
  void createSurface();
  void createSwapChain();
  void createLogicalDevice();
  void pickPhysicalDevice();
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;
  bool isDeviceSuitable(VkPhysicalDevice device) const;

  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const;

  bool checkDeviceExtensionSupport(VkPhysicalDevice device) const;

  VkSurfaceFormatKHR chooseSwapSurfaceFormat(
      const std::vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(
      const std::vector<VkPresentModeKHR> availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
  void mainLoop();
  void updateAppState();
  void updateUniformBuffer();

  void createDescriptorPool();

  void drawFrame();
  void cleanupSwapChain();
  void cleanup();
  void createInstance();
  void setupDebugCallback();

  std::vector<const char *> getRequiredExtensions();

  bool checkValidationLayerSupport();

  BufferMemory createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                            VkMemoryPropertyFlags properties, VkBuffer &buffer,
                            VkDeviceMemory &bufferMemory);

  void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  static VKAPI_ATTR VkBool32 VKAPI_CALL
  dbgFunc(VkDebugReportFlagsEXT msgFlags, VkDebugReportObjectTypeEXT objType,
          uint64_t srcObject, size_t location, int32_t msgCode,
          const char *pLayerPrefix, const char *pMsg, void *pUserData);

  GLFWwindow *window;

  VkInstance instance;
  VkDebugReportCallbackEXT callback;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device;
  VkQueue graphicsQueue;
  VkQueue presentQueue;
  std::vector<VkImage> swapChainImages;
  std::vector<VkImageView> swapChainImageViews;
  std::vector<VkFramebuffer> swapChainFramebuffers;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;
  VkRenderPass renderPass;
  VkDescriptorSetLayout descriptorSetLayout;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
  VkSurfaceKHR surface;
  VkSwapchainKHR swapChain;
  VkCommandPool commandPool;
  VkDescriptorPool descriptorPool;
  VkDescriptorSet descriptorSet;

  std::vector<VkCommandBuffer> commandBuffers;
  VkSemaphore imageAvailableSemaphore;
  VkSemaphore renderFinishedSemaphore;

  // TODO: Group buffer/buffermemory in to a single object
  // TODO: Driver developers recommend that you also store multiple buffers,
  // like the vertex and index buffer, into a single VkBuffer and use offsets in
  // commands like vkCmdBindVertexBuffers
  // https://developer.nvidia.com/vulkan-memory-management
  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
  VkBuffer indexBuffer;
  VkDeviceMemory indexBufferMemory;
  VkBuffer uniformBuffer;
  VkDeviceMemory uniformBufferMemory;
  VkImageView textureImageView;
  VkSampler textureSampler;

  VkImage textureImage;
  VkDeviceMemory textureImageMemory;

  const std::vector<Vertex> vertices = {
      // pos color uv
      {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
      {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
      {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}};

  const std::vector<uint16_t> indices = {0, 1, 2, 2, 3, 0};

  void createTextureImage();
  void createImage(uint32_t width, uint32_t height, VkFormat format,
                   VkImageTiling tiling, VkImageUsageFlags usage,
                   VkMemoryPropertyFlags properties, VkImage &image,
                   VkDeviceMemory &imageMemory);

  VkCommandBuffer beginSingleTimeCommands();
  void endSingleTimeCommands(VkCommandBuffer commandBuffer);
  void transitionImageLayout(VkImage image, VkFormat format,
                             VkImageLayout oldLayout, VkImageLayout newLayout);
  void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width,
                         uint32_t height);

  void createTextureImageView();

  VkImageView createImageView(VkImage image, VkFormat format);

  void createTextureImageSampler();
};

#endif // VULKAN_PLAY_HELLOTRIANGLEAPP_HPP
