#include "vkrax/utils.h"
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

VkName *get_formatted_names(const char *names[], int count){
  VkName *buffer = calloc(count, sizeof(VkName));
  for(int i = 0; i < count; i ++){
    strcpy(buffer[i].buf, names[i]);
  }
  return buffer;
}
