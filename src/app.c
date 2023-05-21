#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "app.h"
#include "constants.h"
static GLFWwindow *app_window = NULL;

// static VkInstance app_instance;
char *validation_layers[] = {"VK_LAYER_KHRONOS_validation"};
const uint32_t validation_layers_count = 1;

#ifdef NDEBUG
const bool enable_validation_layers = false;
#else
const bool enable_validation_layers = true;
#endif

bool check_validation_layer_supprt(void) {
  uint32_t layer_count;
  vkEnumerateInstanceLayerProperties(&layer_count, NULL);
  VkLayerProperties *layer_properties_buffer =
      (VkLayerProperties *)malloc(sizeof(VkLayerProperties) * layer_count);
  vkEnumerateInstanceLayerProperties(&layer_count, layer_properties_buffer);

  for (uint32_t i = 0; i < validation_layers_count; i++) {
    bool layer_found = false;
    for (uint32_t j = 0; j < layer_count; j++) {
      // compare name of listed layers and available layers
      if (strcmp(validation_layers[i], layer_properties_buffer[j].layerName) ==
          0) {
        layer_found = true;
        break;
      }
    }

    if (!layer_found) {
      return false;
    }
  }
  return true;
}

GLFWwindow *initWindow(void) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  GLFWwindow *app_window =
      glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL);
  if (app_window == NULL) {
    fprintf(stderr, "Failed to Create Window: %s\n", WINDOW_NAME);
  }
  return app_window;
}
VkResult createInstance(VkInstance *instance) {
  if (enable_validation_layers && !check_validation_layer_supprt()) {
    return VK_ERROR_LAYER_NOT_PRESENT;
  }

  puts("Creating Instance!");
  VkApplicationInfo app_info;
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "Hello Triangle";
  app_info.pEngineName = "No Engine";
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo create_info;
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;

  // validation_layers
  if (enable_validation_layers) {

    uint32_t inst_layer_count = 1;
    create_info.enabledLayerCount = inst_layer_count;
    char pp_inst_layers[inst_layer_count][VK_MAX_EXTENSION_NAME_SIZE];
    strcpy(pp_inst_layers[0], "VK_LAYER_KHRONOS_validation");
    char *pp_inst_layer_names[inst_layer_count];
    for (uint32_t i = 0; i < inst_layer_count; i++) {
      pp_inst_layer_names[i] = pp_inst_layers[i];
    }
    create_info.enabledLayerCount = inst_layer_count;
    create_info.ppEnabledLayerNames = (const char *const *)pp_inst_layer_names;
  } else {
    create_info.enabledLayerCount = 0;
  }
  // check vulkan support
  if (glfwVulkanSupported() == GLFW_FALSE) {
    printf("Vulkan is not supported!\n");
    return VK_ERROR_UNKNOWN;
  }

  uint32_t glfw_extension_count = 0;
  const char *const *glfw_ext_names =
      glfwGetRequiredInstanceExtensions(&glfw_extension_count);
  printf("%d extensions available!\n", glfw_extension_count);
  for (uint32_t i = 0; i < glfw_extension_count; i++) {
    printf("\t{%s}\n", glfw_ext_names[i]);
  }
  // struct Extensions extensions = glfw_required_extensions();
  create_info.enabledExtensionCount = glfw_extension_count;
  create_info.ppEnabledExtensionNames = glfw_ext_names;

  puts("here");
  VkResult result = vkCreateInstance(&create_info, NULL, instance);
  puts("no here");
  return result;
}
VkResult initVulkan(VkInstance *instance) {
  VkResult instance_result = createInstance(instance);
  if (instance_result != VK_SUCCESS) {
    puts("Failed to Create Instance");
    return instance_result;
  }
  return instance_result;
}
void mainLoop(GLFWwindow *window) {
  app_window = window;
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

void cleanup(VkInstance *instance, GLFWwindow *window) {
  vkDestroyInstance(*instance, NULL);
  glfwDestroyWindow(window);
  glfwTerminate();
}

int run(void) {
  int exit_status = 0;
  VkInstance instance;
  GLFWwindow *window = initWindow();
  VkResult vulkan_init = initVulkan(&instance);
  if (VK_SUCCESS != vulkan_init) {
    printf("Relevant Error: %s\n", vk_result_char(vulkan_init));
    exit_status = EXIT_FAILURE;
    goto CleanShit;
  }
  mainLoop(window);
CleanShit:
  cleanup(&instance, window);
  return exit_status;
}
