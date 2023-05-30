#pragma once

#include <GLFW/glfw3.h>

GLFWwindow *init_window(void);
void main_loop(GLFWwindow *window);
void process_input(GLFWwindow *window);

