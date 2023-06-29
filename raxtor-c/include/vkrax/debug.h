#ifndef RAX_DEBUG_H
#define RAX_DEBUG_H
#include <vulkan/vulkan.h>


VKAPI_ATTR VkBool32 VKAPI_CALL
debug_callback_fn(VkDebugUtilsMessageSeverityFlagBitsEXT message_severety,
               VkDebugUtilsMessageTypeFlagsEXT message_type,
               const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
               void *p_user_data);

VkResult create_debug_utils_messenger_ext(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *p_create_info,
    VkAllocationCallbacks *p_allocator,
    VkDebugUtilsMessengerEXT *p_debug_messenger);

void destroy_utils_messenger_ext(VkInstance instance,
                                 VkDebugUtilsMessengerEXT debug_messenger,
                                 const VkAllocationCallbacks *p_allocator);


void populate_debug_messenger_create_info(
    VkDebugUtilsMessengerCreateInfoEXT *create_info,
    PFN_vkDebugUtilsMessengerCallbackEXT callback);


void setup_debug_messenger(VkInstance instance);
#endif
