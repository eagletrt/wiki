#include "config_utils.h"

config_t* newConfig() {
    config_t *config = (config_t*) malloc(sizeof(config_t));
    
    config->mqtt.host = strdup("localhost");
    config->mqtt.port = 1883;
    config->mqtt.data_topic = strdup("telemetria");
    config->mqtt.log_topic = strdup("telemetria_log");
    config->mongodb.host = strdup("localhost");
    config->mongodb.port = 27017;
    config->mongodb.db = strdup("eagle_test");
    config->mongodb.collection = strdup("chimera");
    config->gps.plugged = 1;
    config->gps.simulated = 1;
    config->gps.interface = strdup("/dev/pts/4");
    config->pilots_count = 6;
    config->pilots = (char**) malloc(sizeof(char*) * config->pilots_count);
    config->pilots[0] = strdup("default");
    config->pilots[1] = strdup("Ivan");
    config->pilots[2] = strdup("Filippo");
    config->pilots[3] = strdup("Mirco");
    config->pilots[4] = strdup("Nicola");
    config->pilots[5] = strdup("Davide");
    config->races_count = 5;
    config->races = (char**) malloc(sizeof(char*) * config->races_count);
    config->races[0] = strdup("default");
    config->races[1] = strdup("Autocross");
    config->races[2] = strdup("Skidpad");
    config->races[3] = strdup("Endurance");
    config->races[4] = strdup("Acceleration");
    config->circuits_count = 4;
    config->circuits = (char**) malloc(sizeof(char*) * config->circuits_count);
    config->circuits[0] = strdup("default");
    config->circuits[1] = strdup("Vadena");
    config->circuits[2] = strdup("Varano");
    config->circuits[3] = strdup("Povo");
    config->can_interface = strdup("can0");
    config->sending_rate = 500;
    config->verbose = 0;
    

    return config;
}