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

  uint32_t findMemoryType(uint32_t typeFilter,
                          VkMemoryPropertyFlags properties);
  void recreateSwapChain();
  void createSemaphores();
  void createCommandBuffers();
  void createCommandPool();
  void createFramebuffers();
  void createRenderPass();
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
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
  VkSurfaceKHR surface;
  VkSwapchainKHR swapChain;
  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;
  VkSemaphore imageAvailableSemaphore;
  VkSemaphore renderFinishedSemaphore;
  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;

  const std::vector<Vertex> vertices = {{{-0.75f, -0.75f}, {1.0f, 1.0f, 1.0f}},
                                        {{0.75f, 0.75f}, {0.0f, 1.0f, 0.0f}},
                                        {{-0.75f, 0.75f}, {0.0f, 0.0f, 1.0f}},
                                        {{0.25f, -0.25f}, {1.0f, 0.0f, 0.0f}},
                                        {{0.25f, 0.25f}, {0.0f, 1.0f, 0.0f}},
                                        {{-0.25f, 0.25f}, {0.0f, 0.0f, 1.0f}}};
};

#endif // VULKAN_PLAY_HELLOTRIANGLEAPP_HPP
