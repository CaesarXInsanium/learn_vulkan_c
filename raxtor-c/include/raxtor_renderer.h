#ifndef RAXTOR_ENGINE_H
#define RAXTOR_ENGINE_H

#include <vulkan/vulkan.h>

typedef struct {
  VkInstance instance;
} RaxtorEngine;

void raxtor_startup(RaxtorEngine *render);

void raxtor_shutdown(RaxtorEngine *render);

#endif
