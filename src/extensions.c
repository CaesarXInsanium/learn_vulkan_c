#include "extensions.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

struct Extensions glfw_required_extensions(void) {
  struct Extensions result;
  uint32_t glfw_extension_count = 0;
  const char **glfw_extensions = NULL;
  glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
  char **extensions = (char **)malloc(sizeof(char *) * glfw_extension_count);
  printf("GLFW extensions!\tCount: %d\n", glfw_extension_count);
  for (int i = 0; i < glfw_extension_count; i++) {
    printf("%s\n", glfw_extensions[i]);
    int len = strlen(glfw_extensions[i]);
    char *str = (char *)malloc(sizeof(char) * len);
    strcpy(str, glfw_extensions[i]);
    extensions[i] = str;
  }
  result.extensions = extensions;
  result.count = glfw_extension_count;
  return result;
}

struct Extensions possible_extensions(void) {

  // generate required extensions
  uint32_t extension_count = 0;
  // get count of prperties
  vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);
  // allocate buffer to hold properties
  VkExtensionProperties *properties_buffer = (VkExtensionProperties *)malloc(
      sizeof(VkExtensionProperties) * extension_count);
  // use them
  vkEnumerateInstanceExtensionProperties(NULL, &extension_count,
                                         properties_buffer);

  struct Extensions result;
  char *extensions_names[VK_MAX_EXTENSION_NAME_SIZE];
  // malloc(
  //     sizeof(char[VK_MAX_EXTENSION_NAME_SIZE]) * extension_count);

  for (int i = 0; i < extension_count; i++) {
    strcpy(extensions_names[i], properties_buffer[i].extensionName);
  }
  result.extensions = extensions_names;
  result.count = extension_count;
  return result;
}

void print_extensions(struct Extensions ext) {
  printf("%d extensions available!\n", ext.count);
  for (int i = 0; i < ext.count; i++) {
    printf("\tExtension: %s\n", ext.extensions[i]);
  }
}

char** 

void Extensions_destroy(struct Extensions self) {
  for (int i = 0; i < self.count; i++) {
    free(self.extensions[i]);
  }
  free(self.extensions);
}
