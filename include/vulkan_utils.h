#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

VkResult create_instance(VkInstance *instance, bool enable_validation_layers, bool validation_checker(void), const char *name, );
VkResult init_vulkan(VkInstance *instance, void debug_setup(VkInstance *x));
