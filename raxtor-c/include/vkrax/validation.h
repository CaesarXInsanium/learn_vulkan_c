#ifndef RAX_VALIDATION_H
#define RAX_VALIDATION_H

#include "vkrax/utils.h"
#include <stdbool.h>
#include <stdint.h>
#define enable_validation_layers 0

char *get_supported_validation_layers(uint32_t *layer_count);

#endif
