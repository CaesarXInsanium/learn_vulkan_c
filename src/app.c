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
// this shit will only work if vulkan validation layers are installed
char *validation_layers[] = {
    "VK_LAYER_KHRONOS_validation", "VK_LAYER_INTEL_nullhw",
    "VK_LAYER_KHRONOS_validation", "VK_LAYER_LUNARG_api_dump",
    "VK_LAYER_LUNARG_monitor",     "VK_LAYER_LUNARG_screenshot",
    "VK_LAYER_MESA_device_select", "VK_LAYER_MESA_overlay",
    "VK_LAYER_RENDERDOC_Capture",
};
const uint32_t validation_layers_count = 8;

#ifdef NDEBUG
const bool enable_validation_layers = false;
#else
const bool enable_validation_layers = true;
#endif

bool check_validation_layer_support(void) {
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

VKAPI_ATTR VkBool32 VKAPI_CALL
debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severety,
               VkDebugUtilsMessageTypeFlagsEXT message_type,
               const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
               void *p_user_data) {
  fprintf(stderr, "Validation Layer: %s\n%p%p\nUser Data: %p\n",
          p_callback_data->pMessage, (void *)&message_severety,
          (void *)&message_type, p_user_data);
  ;
  return VK_FALSE;
}

VkResult create_debug_utils_messenger_ext(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *p_create_info,
    VkAllocationCallbacks *p_allocator,
    VkDebugUtilsMessengerEXT *p_debug_messenger) {
  PFN_vkCreateDebugUtilsMessengerEXT func =
      (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
          instance, "VkDebugUtilsMessengerCreateInfoEXT");

  if (func == NULL) {
    return func(instance, p_create_info, p_allocator, p_debug_messenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

void destroy_utils_messenger_ext(
  VkInstance instance,
  VkDebugUtilsMessengerEXT debug_messenger,
  const VkAllocationCallbacks *p_allocator
){
  PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
    instance,
    "vkDestroyDEbugUtilsMessengerEXT"
  );

  if (func != NULL){
    func(instance, debug_messenger, p_allocator);
  }
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
  if (enable_validation_layers && !check_validation_layer_support()) {
    return VK_ERROR_LAYER_NOT_PRESENT;
  }

  puts("Creating Instance!");
  VkApplicationInfo app_info;
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pNext = NULL;
  app_info.pApplicationName = "Hello Triangle";
  app_info.pEngineName = "No Engine";
  app_info.engineVersion = VK_MAKE_VERSION(0, 0, 1);
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo create_info;
  {};
  create_info.pNext = NULL;
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;

  // validation_layers
  if (enable_validation_layers) {

    create_info.enabledLayerCount = validation_layers_count;
    create_info.ppEnabledLayerNames = (const char *const *)validation_layers;
  } else {
    create_info.enabledLayerCount = 0;
  }
  // check vulkan support
  if (glfwVulkanSupported() == GLFW_FALSE) {
    printf("Vulkan is not supported!\n");
    return VK_ERROR_UNKNOWN;
  }

  // extensions
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

  VkResult result = vkCreateInstance(&create_info, NULL, instance);

  return result;
}
void setupDebugMessenger(VkInstance instance) {
  if (!enable_validation_layers)
    return;
  VkDebugUtilsMessengerCreateInfoEXT create_info;
  {};
  create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  create_info.messageSeverity =
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  // 53
  create_info.pfnUserCallback = debug_callback;
  create_info.pUserData = NULL;
  if (create_debug_utils_messenger_ext(instance, &create_info, NULL,
                                       debug_messenger) != VK_SUCCESS) {
    fprintf(stderr, "Failed to Setup Debug Messenger!\n");
    exit(1);
  }
}
VkResult initVulkan(VkInstance *instance) {
  VkResult instance_result = createInstance(instance);
  if (instance_result != VK_SUCCESS) {
    puts("Failed to Create Instance");
    return instance_result;
  }

  setupDebugMessenger(*instance);

  return instance_result;
}
void mainLoop(GLFWwindow *window) {
  app_window = window;
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

// page 55
void cleanup(VkInstance *instance, GLFWwindow *window) {
  if(enable_validation_layers){
    destroy_utils_messenger_ext(*instance, debug_messenger, NULL);
  }
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
