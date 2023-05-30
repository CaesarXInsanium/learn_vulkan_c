#include "vulkan_utils.h"
#include <vulkan/vulkan.h>

VkResult init_vulkan(VkInstance *instance, void debug_setup(VkInstance *x)){

  VkResult instance_result = create_instance(instance);
  if (instance_result != VK_SUCCESS) {
    puts("Failed to Create Instance");
    return instance_result;
  }

  setupDebugMessenger(*instance);

  return instance_result;
}
