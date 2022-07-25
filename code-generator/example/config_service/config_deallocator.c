#include "config_utils.h"

void deleteConfig(config_t *config) {
    free(config->mqtt.host);
    free(config->mqtt.data_topic);
    free(config->mqtt.log_topic);
    free(config->mongodb.host);
    free(config->mongodb.db);
    free(config->mongodb.collection);
    free(config->gps.interface);
    freeStringsArray(config->pilots, &config->pilots_count);
    freeStringsArray(config->races, &config->races_count);
    freeStringsArray(config->circuits, &config->circuits_count);
    free(config->can_interface);
    
}