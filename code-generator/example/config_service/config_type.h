#ifndef TELEMETRY_CONFIG_UTILS
#define TELEMETRY_CONFIG_UTILS

/* IMPORTS */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../misc_utils/misc_utils.h"
#include "./jsmn/jsmn.h"

/* STRUCTURES */

typedef struct {
	char* host;
	int port;
	char* data_topic;
	char* log_topic;
} mqtt_config_t;

typedef struct {
	char* host;
	int port;
	char* db;
	char* collection;
} mongodb_config_t;

typedef struct {
	int plugged;
	int simulated;
	char* interface;
} gps_config_t;

typedef struct {
	mqtt_config_t mqtt;
	mongodb_config_t mongodb;
	gps_config_t gps;
	char** pilots;
	int pilots_count;
	char** races;
	int races_count;
	char** circuits;
	int circuits_count;
	char* can_interface;
	int sending_rate;
	int verbose;
} config_t;


/* FUNCTIONS */

config_t* newConfig();
void parseConfigFile(const char* path, config_t **config);
void deleteConfig(config_t *config);
void printConfig(const config_t* config);

#endif