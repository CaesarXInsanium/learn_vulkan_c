#include <GLFW/glfw3.h>
#include "window.h"
#include <stdio.h>
#include "constants.h"

GLFWwindow *init_window(void) {
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
