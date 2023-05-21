#include <cglm/types.h>
#include <stdint.h>
#include <vulkan/vulkan_core.h>
#include "app.h"
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <vulkan/vulkan.h>

int main(int argc, char **argv) {
  printf("Argument Count: %d\nArguments: %p\n", argc, (void *)argv);
  int result = run();
  return result;
}
