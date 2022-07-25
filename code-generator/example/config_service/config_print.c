#include "config_utils.h"

void printConfig(const config_t* config) {
    printf("config->mqtt.host:\t%s\n", config->mqtt.host);
    printf("config->mqtt.port:\t%d\n", config->mqtt.port);
    printf("config->mqtt.data_topic:\t%s\n", config->mqtt.data_topic);
    printf("config->mqtt.log_topic:\t%s\n", config->mqtt.log_topic);
    printf("config->mongodb.host:\t%s\n", config->mongodb.host);
    printf("config->mongodb.port:\t%d\n", config->mongodb.port);
    printf("config->mongodb.db:\t%s\n", config->mongodb.db);
    printf("config->mongodb.collection:\t%s\n", config->mongodb.collection);
    printf("config->gps.plugged:\t%d\n", config->gps.plugged);
    printf("config->gps.simulated:\t%d\n", config->gps.simulated);
    printf("config->gps.interface:\t%s\n", config->gps.interface);
    printf("config->pilots: ");
    printStringsArray(config->pilots, config->pilots_count);
    printf("config->races: ");
    printStringsArray(config->races, config->races_count);
    printf("config->circuits: ");
    printStringsArray(config->circuits, config->circuits_count);
    printf("config->can_interface:\t%s\n", config->can_interface);
    printf("config->sending_rate:\t%d\n", config->sending_rate);
    printf("config->verbose:\t%d\n", config->verbose);
    
}