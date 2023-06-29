#include "constants.h"
#include "vkrax/utils.h"
#include "window.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include "app.h"
#include "raxtor_renderer.h"
#include <GLFW/glfw3.h>

static GLFWwindow *focused_window = NULL;

void App_init(struct App *app) {
  app->window = init_window();
  RaxtorEngine engine;
  raxtor_startup(&engine);
  app->engine = engine;
}
void App_run(struct App *app) {
  focused_window = app->window;

  while (!glfwWindowShouldClose(app->window)) {
    process_input(app->window);
    glfwSwapBuffers(app->window);
  }
}
void App_cleanup(struct App *app) {
  raxtor_shutdown(&app->engine);
  glfwWindowShouldClose(app->window);
  glfwTerminate();
}

void process_input(GLFWwindow *window) {
  UNUSED(window);
  glfwPollEvents();
}

// page 55
// void cleanup(VkInstance *instance, GLFWwindow *window) {
//   if (enable_validation_layers) {
//     destroy_utils_messenger_ext(*instance, debug_messenger, NULL);
//   }
//   vkDestroyInstance(*instance, NULL);
//   glfwDestroyWindow(window);
//   glfwTerminate();
// }

// int run(void) {
//   int exit_status = 0;
//   VkInstance instance;
//   GLFWwindow *window = init_window();
//   VkResult vulkan_init = initVulkan(&instance);
//   if (VK_SUCCESS != vulkan_init) {
//     printf("Relevant Error: %s\n", vk_result_char(vulkan_init));
//     exit_status = EXIT_FAILURE;
//     goto CleanShit;
//   }
//   mainLoop(window);
// CleanShit:
//   cleanup(&instance, window);
//   return exit_status;
// }
//
// void process_input(GLFWwindow *window) {
//   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//     glfwSetWindowShouldClose(window, GLFW_TRUE);
// }
