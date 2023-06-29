#include "vkrax/validation.h"
#include "vkrax/debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

VkDebugUtilsMessengerEXT debug_messenger;

VKAPI_ATTR VkBool32 VKAPI_CALL
debug_callback_fn(VkDebugUtilsMessageSeverityFlagBitsEXT message_severety,
                  VkDebugUtilsMessageTypeFlagsEXT message_type,
                  const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
                  void *p_user_data) {
  fprintf(stdout, "Validation Layer: %s\n%p%p\nUser Data: %p\n",
          p_callback_data->pMessage, (void *)&message_severety,
          (void *)&message_type, p_user_data);
  ;
  return VK_FALSE;
}

VkResult create_debug_utils_messenger_ext(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *p_create_info,
    VkAllocationCallbacks *p_allocator,
    VkDebugUtilsMessengerEXT *p_debug_messenger) {
  PFN_vkCreateDebugUtilsMessengerEXT func =
      (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
          instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != NULL) {
    return func(instance, p_create_info, p_allocator, p_debug_messenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

void destroy_utils_messenger_ext(VkInstance instance,
                                 VkDebugUtilsMessengerEXT debug_messenger,
                                 const VkAllocationCallbacks *p_allocator) {
  PFN_vkDestroyDebugUtilsMessengerEXT func =
      (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
          instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != NULL) {
    func(instance, debug_messenger, p_allocator);
  }
}

void populate_debug_messenger_create_info(
    VkDebugUtilsMessengerCreateInfoEXT *create_info,
    PFN_vkDebugUtilsMessengerCallbackEXT callback) {
  create_info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

  create_info->pNext = NULL;
  create_info->flags = 0;
  create_info->messageSeverity =
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  create_info->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

  create_info->pfnUserCallback = callback;
  create_info->pUserData = NULL;
}

void setup_debug_messenger(VkInstance instance) {
  if (!enable_validation_layers)
    return;
  VkDebugUtilsMessengerCreateInfoEXT create_info;
  populate_debug_messenger_create_info(&create_info, debug_callback_fn);
  if (create_debug_utils_messenger_ext(instance, &create_info, NULL,
                                       &debug_messenger) != VK_SUCCESS) {
    fprintf(stderr, "Failed to Setup Debug Messenger!\n");
    return;
  }
}
