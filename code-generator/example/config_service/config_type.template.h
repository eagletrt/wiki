#ifndef TELEMETRY_CONFIG_UTILS
#define TELEMETRY_CONFIG_UTILS

/* IMPORTS */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../misc_utils/misc_utils.h"
#include "./jsmn/jsmn.h"

/* STRUCTURES */

// {{GENERATE_CONFIG_TYPE}}

/* FUNCTIONS */

config_t* newConfig();
void parseConfigFile(const char* path, config_t **config);
void deleteConfig(config_t *config);
void printConfig(const config_t* config);

#endif