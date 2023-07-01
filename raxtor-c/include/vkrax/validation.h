#ifndef RAX_VALIDATION_H
#define RAX_VALIDATION_H

#include "vkrax/utils.h"
#include <stdbool.h>
#include <stdint.h>

#ifndef DEBUGS
#define enable_validation_layers 1
#else
#define enable_validation_layers 0
#endif

char *get_supported_validation_layers(uint32_t *layer_count);

#endif
