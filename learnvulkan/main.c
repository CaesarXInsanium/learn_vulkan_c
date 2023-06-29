#include <stdint.h>
#include "app.h"
#include <cglm/cglm.h>
#include <stdio.h>
#include <vulkan/vulkan.h>

int main(int argc, char **argv) {
  printf("Argument Count: %d\nArguments: %p\n", argc, (void *)argv);
  struct App app;
  App_init(&app);
  App_run(&app);
  App_cleanup(&app);
}
