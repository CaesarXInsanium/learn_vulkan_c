#pragma once
#include <stdint.h>
#include <vulkan/vulkan_core.h>

// everything here is heap allocated so it MUST BE FREED
struct Extensions {
  char **extensions;
  uint32_t count;
};

struct Extensions glfw_required_extensions(void);

struct Extensions possible_extensions(void);

struct Extensions join_extensions(struct Extensions a, struct Extensions b);
void print_extensions(struct Extensions ext);

void Extensions_destroy(struct Extensions self);
