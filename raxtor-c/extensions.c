#include "vkrax/extensions.h"
#include "vkrax/utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

VkName *get_supported_extensions(uint32_t *extension_count) {
  vkEnumerateInstanceExtensionProperties(NULL, extension_count, NULL);
  VkExtensionProperties *extension_buffer =
      calloc(*extension_count, sizeof(VkExtensionProperties));
  vkEnumerateInstanceExtensionProperties(NULL, extension_count,
                                         extension_buffer);

  VkName *result_buffer = malloc(sizeof(VkName) * (*extension_count));

  for (uint32_t i = 0; i < *extension_count; i++) {
    strcpy(result_buffer[i].buf, extension_buffer->extensionName);
  }

  return result_buffer;
}
