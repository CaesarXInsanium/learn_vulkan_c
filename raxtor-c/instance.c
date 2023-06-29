#include "vkrax/instance.h"
#include "vkrax/debug.h"
#include "vkrax/extensions.h"
#include "vkrax/utils.h"
#include "vkrax/validation.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

VkResult create_instance(VkInstance *instance) {
  if (enable_validation_layers) {
    fprintf(stderr, "Failed to Load Validation Layers\n");
    printf("Loading without\n");
    return VK_ERROR_LAYER_NOT_PRESENT;
  }

  puts("Creating Instance!");
  VkApplicationInfo app_info;
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pNext = NULL;
  app_info.pApplicationName = "Hello Triangle";
  app_info.pEngineName = "No Engine";
  app_info.engineVersion = VK_MAKE_VERSION(0, 0, 1);
  app_info.apiVersion = VK_API_VERSION_1_3;

  // VkDebugUtilsMessengerCreateInfoEXT debug_create_info;

  VkInstanceCreateInfo create_info;
  {};
  create_info.pNext = NULL;
  create_info.flags = 0;
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;

  // validation_layers
  if (!enable_validation_layers) {
    fprintf(stderr, "Validation layers not supported!\n");
    return VK_ERROR_UNKNOWN;
  } else {
    create_info.enabledLayerCount = 0;
    create_info.pNext = NULL;
  }
  // check vulkan support
  if (glfwVulkanSupported() == GLFW_FALSE) {
    fprintf(stderr, "Vulkan is not supported!\n");
    return VK_ERROR_UNKNOWN;
  }

  uint32_t count = 0;
  VkName *extension_names = get_supported_extensions(&count);
  create_info.enabledExtensionCount = count;
  create_info.ppEnabledExtensionNames = (const char *const *)extension_names;

  VkResult result = vkCreateInstance(&create_info, NULL, instance);

  return result;
}
