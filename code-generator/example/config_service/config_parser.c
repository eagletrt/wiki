#include "config_utils.h"

/* INTERNAL FUNCTIONS SIGNATURES AND CONSTANTS */

static const int MAX_TOKENS_COUNT = 100;
static int getJsonString(FILE *config_file, char **json_string);
static int getJsonTokens(const char* json_string, int json_length, jsmntok_t** json_tokens);
static char* extractString(jsmntok_t token, const char *json_string);
static char* getStringValue(const jsmntok_t *json_tokens, const char *json_string, int *i);
static int getIntValue(const jsmntok_t *json_tokens, const char *json_string, int *i);
static char** getStringArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i);
static int* getIntArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i);
static double* getDoubleArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i);
static void parseMqttObject(const jsmntok_t *json_tokens, const char *json_string, config_t *config, int *i);
static void parseMongodbObject(const jsmntok_t *json_tokens, const char *json_string, config_t *config, int *i);
static void parseJsonTokens(const jsmntok_t *json_tokens, int tokens_length, const char *json_string, config_t *config);

/* EXPORTED FUNCTIONS */

static void parseMqttObject(const jsmntok_t *json_tokens, const char *json_string, config_t *config, int *i) {
	++(*i);
	int size = json_tokens[*i].size;
	for (int j = 0; j < size; ++j) {
		++(*i);
		char* key = extractString(json_tokens[*i], json_string);
		if (strcmp(key, "host") == 0) {
			free(config->mqtt.host);
			config->mqtt.host = getStringValue(json_tokens, json_string, i);
		}
		else if (strcmp(key, "port") == 0) {
			config->mqtt.port = getIntValue(json_tokens, json_string, i);
		}
		else if (strcmp(key, "data_topic") == 0) {
			free(config->mqtt.data_topic);
			config->mqtt.data_topic = getStringValue(json_tokens, json_string, i);
		}
		else if (strcmp(key, "log_topic") == 0) {
			free(config->mqtt.log_topic);
			config->mqtt.log_topic = getStringValue(json_tokens, json_string, i);
		}
		else {
			++(*i);
			jsmntok_t token = json_tokens[*i];
			switch (token.type)
			{
				case JSMN_ARRAY:
					*i += token.size;
					break;
				case JSMN_OBJECT:
					*i += 2 * token.size;
					break;
			}
		}
	}
}

static void parseMongodbObject(const jsmntok_t *json_tokens, const char *json_string, config_t *config, int *i) {
	++(*i);
	int size = json_tokens[*i].size;
	for (int j = 0; j < size; ++j) {
		++(*i);
		char* key = extractString(json_tokens[*i], json_string);
		if (strcmp(key, "host") == 0) {
			free(config->mongodb.host);
			config->mongodb.host = getStringValue(json_tokens, json_string, i);
		}
		else if (strcmp(key, "port") == 0) {
			config->mongodb.port = getIntValue(json_tokens, json_string, i);
		}
		else if (strcmp(key, "db") == 0) {
			free(config->mongodb.db);
			config->mongodb.db = getStringValue(json_tokens, json_string, i);
		}
		else if (strcmp(key, "collection") == 0) {
			free(config->mongodb.collection);
			config->mongodb.collection = getStringValue(json_tokens, json_string, i);
		}
		else {
			++(*i);
			jsmntok_t token = json_tokens[*i];
			switch (token.type)
			{
				case JSMN_ARRAY:
					*i += token.size;
					break;
				case JSMN_OBJECT:
					*i += 2 * token.size;
					break;
			}
		}
	}
}

static void parseGpsObject(const jsmntok_t *json_tokens, const char *json_string, config_t *config, int *i) {
	++(*i);
	int size = json_tokens[*i].size;
	for (int j = 0; j < size; ++j) {
		++(*i);
		char* key = extractString(json_tokens[*i], json_string);
		if (strcmp(key, "plugged") == 0) {
			config->gps.plugged = getIntValue(json_tokens, json_string, i);
		}
		else if (strcmp(key, "simulated") == 0) {
			config->gps.simulated = getIntValue(json_tokens, json_string, i);
		}
		else if (strcmp(key, "interface") == 0) {
			free(config->gps.interface);
			config->gps.interface = getStringValue(json_tokens, json_string, i);
		}
		else {
			++(*i);
			jsmntok_t token = json_tokens[*i];
			switch (token.type)
			{
				case JSMN_ARRAY:
					*i += token.size;
					break;
				case JSMN_OBJECT:
					*i += 2 * token.size;
					break;
			}
		}
	}
}

static void parseJsonTokens(const jsmntok_t *json_tokens, int tokens_length, const char *json_string, config_t *config) {
	int _i, *i = &_i;
	for (*i = 1; *i < tokens_length; ++(*i)) {
		char* key = extractString(json_tokens[*i], json_string);
		if (strcmp(key, "mqtt") == 0) {
			parseMqttObject(json_tokens, json_string, config, i);
		}
		else if (strcmp(key, "mongodb") == 0) {
			parseMongodbObject(json_tokens, json_string, config, i);
		}
		else if (strcmp(key, "gps") == 0) {
			parseGpsObject(json_tokens, json_string, config, i);
		}
		else if (strcmp(key, "pilots") == 0) {
			freeStringsArray(config->pilots, &config->pilots_count);
			config->pilots = getStringArrayValue(json_tokens, json_string, &config->pilots_count, i);
		}
		else if (strcmp(key, "races") == 0) {
			freeStringsArray(config->races, &config->races_count);
			config->races = getStringArrayValue(json_tokens, json_string, &config->races_count, i);
		}
		else if (strcmp(key, "circuits") == 0) {
			freeStringsArray(config->circuits, &config->circuits_count);
			config->circuits = getStringArrayValue(json_tokens, json_string, &config->circuits_count, i);
		}
		else if (strcmp(key, "can_interface") == 0) {
			free(config->can_interface);
			config->can_interface = getStringValue(json_tokens, json_string, i);
		}
		else if (strcmp(key, "sending_rate") == 0) {
			config->sending_rate = getIntValue(json_tokens, json_string, i);
		}
		else if (strcmp(key, "verbose") == 0) {
			config->verbose = getIntValue(json_tokens, json_string, i);
		}
		else {
			++(*i);
			jsmntok_t token = json_tokens[*i];
			switch (token.type)
			{
				case JSMN_ARRAY:
					*i += token.size;
					break;
				case JSMN_OBJECT:
					*i += 2 * token.size;
					break;
			}
		}
	}
}


/* INTERNAL FUNCTIONS DEFINITIONS */

static int getJsonString(FILE *config_file, char **json_string) {
    char* line;
    size_t lineLength = 0;
    int json_length = 0;

    getline(&line, &lineLength, config_file);
    json_length += lineLength;
    *json_string = (char*) malloc(sizeof(char) * json_length);
	strcpy(*json_string, line);

    while (getline(&line, &lineLength, config_file) != -1) {       	
		json_length += lineLength;
		*json_string = (char*) realloc(*json_string, sizeof(char) * json_length);
		strcat(*json_string, line);
    }

    return json_length;
}

static int getJsonTokens(const char* json_string, int json_length, jsmntok_t** json_tokens) {
    jsmn_parser parser;
    jsmn_init(&parser);
    *json_tokens = (jsmntok_t*) malloc(sizeof(jsmntok_t) * MAX_TOKENS_COUNT);
    int tokens_length = jsmn_parse(&parser, json_string, json_length, *json_tokens, MAX_TOKENS_COUNT);
    return tokens_length;
}

static char* extractString(jsmntok_t token, const char *json_string) {
    unsigned int length = token.end - token.start;
    char* key = malloc(sizeof(char) * (length + 1));
	memcpy(key, &json_string[token.start], length);
	key[length] = '\0';
    return key;
}

static char* getStringValue(const jsmntok_t *json_tokens, const char *json_string, int *i) {
    ++(*i);
    const jsmntok_t token = json_tokens[*i];
    return extractString(token, json_string);
}

static int getIntValue(const jsmntok_t *json_tokens, const char *json_string, int *i) {
    ++(*i);
    const jsmntok_t token = json_tokens[*i];
    return atoi(extractString(token, json_string));
}

static double getDoubleValue(const jsmntok_t *json_tokens, const char *json_string, int *i) {
    ++(*i);
    const jsmntok_t token = json_tokens[*i];
    return atof(extractString(token, json_string));
}

static char** getStringArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i) {
    char **string_array;

    ++(*i);
    *size = json_tokens[*i].size;
    string_array = (char**) malloc(sizeof(char*) * *size);

    for (int j = 0; j < *size; ++j) {
        ++(*i);
        char* child = extractString(json_tokens[*i], json_string);
        string_array[j] = child;
    }

    return string_array;
}

static int* getIntArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i) {
    int *int_array;

    ++(*i);
    *size = json_tokens[*i].size;
    int_array = (int*) malloc(sizeof(int) * *size);

    for (int j = 0; j < *size; ++j) {
        ++(*i);
        char* child = extractString(json_tokens[*i], json_string);
        int_array[j] = atoi(child);
    }

    return int_array;
}

static double* getDoubleArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i) {
    double *double_array;

    ++(*i);
    *size = json_tokens[*i].size;
    double_array = (double*) malloc(sizeof(double) * *size);

    for (int j = 0; j < *size; ++j) {
        ++(*i);
        char* child = extractString(json_tokens[*i], json_string);
        double_array[j] = atof(child);
    }

    return double_array;
}