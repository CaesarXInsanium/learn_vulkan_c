#pragma once
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "raxtor_renderer.h"
#include <stdint.h>

struct App{
  GLFWwindow *window;
  size_t window_dim[2];
  RaxtorEngine engine;
};

void App_init(struct App *app);
void App_run(struct App *app);
void App_cleanup(struct App *app);

void process_input(GLFWwindow *window);

