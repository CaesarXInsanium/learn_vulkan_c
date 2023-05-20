#include <cglm/types.h>
#include <stdint.h>
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <vulkan/vulkan.h>

int main(int argc, char **argv) {

  puts("Entering GLFW!");
  if (!glfwInit()) {
    goto EndGlfw;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow *window = glfwCreateWindow(800, 600, "VulkanC", NULL, NULL);
  if (NULL == window) {
    goto EndGlfw;
  }

  uint32_t extension_count = 0;
  vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);
  printf("%d extensions supported!\n", extension_count);

  mat4 identity_matrix = {
      {1.0, 0.0, 0.0, 0.0},
      {0.0, 1.0, 0.0, 0.0},
      {0.0, 0.0, 1.0, 0.0},
      {0.0, 0.0, 0.0, 1.0},
  };
  printf("Matrix: %p\n", identity_matrix);

  while (!glfwWindowShouldClose(window)){
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
EndGlfw:
  printf("Exiting GLFW!\n");
  glfwTerminate();
  return 0;
}
