#pragma once
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdint.h>

int run(void);
GLFWwindow *initWindow(void);
void cleanup(VkInstance *instance, GLFWwindow *window);

