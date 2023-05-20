#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "app.h"
void initVulkan(void);
void mainLoop();
void cleanup();

int run(void){
  initVulkan();
  mainLoop();
  cleanup();
}
