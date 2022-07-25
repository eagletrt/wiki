#include "config_utils.h"

config_t* newConfig() {
    config_t *config = (config_t*) malloc(sizeof(config_t));
    
    // {{GENERATE_CONFIG_ALLOCATOR}}

    return config;
}