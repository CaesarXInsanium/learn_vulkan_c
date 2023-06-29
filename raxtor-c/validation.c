#include "vkrax/validation.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>


char *get_supported_validation_layers(uint32_t *layer_count) {
  vkEnumerateInstanceLayerProperties(layer_count, NULL);

  VkLayerProperties *properties_buffer =
      calloc(*layer_count, sizeof(VkLayerProperties));
  vkEnumerateInstanceLayerProperties(layer_count, properties_buffer);

  size_t buffer_size = sizeof(char) * (*layer_count) * VK_MAX_DESCRIPTION_SIZE;
  char *buffer = (char *)malloc(buffer_size);

  for (uint32_t i = 0; i < *layer_count; i++) {
    size_t buffer_index = i * VK_MAX_DESCRIPTION_SIZE;
    strcpy(buffer + buffer_index, properties_buffer[i].layerName);
  }

  return buffer;
}
