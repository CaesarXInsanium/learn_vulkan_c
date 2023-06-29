#ifndef RAX_UTILS_H
#define RAX_UTILS_H

#define UNUSED(x) (void)x

#include <vulkan/vulkan.h>

typedef struct {
  char buf[VK_MAX_EXTENSION_NAME_SIZE];
} VkName;


VkName *formatted_extensions_names(const char *names[], int count);

#endif
