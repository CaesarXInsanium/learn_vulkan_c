#include "raxtor_renderer.h"
#include "vkrax/instance.h"


void raxtor_startup(RaxtorEngine *render){
  VkInstance instance;
  create_instance(&instance);
  render->instance = instance;
}

void raxtor_shutdown(RaxtorEngine *render) {
  vkDestroyInstance(render->instance, NULL);
}
