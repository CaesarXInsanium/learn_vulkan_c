#ifndef RAX_INSTANCE_H
#define RAX_INSTANCE_H
#include "vkrax/extensions.h"
#include "vkrax/validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

VkResult create_instance(VkInstance *instance);
void populate_instance_create_info(VkApplicationInfo info);
#endif
