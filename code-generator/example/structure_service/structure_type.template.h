#ifndef TELEMETRY_STRUCTURE_SERVICE
#define TELEMETRY_STRUCTURE_SERVICE

/* IMPORTS */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* TYPES */

// {{GENERATE_STRUCTURE_TYPE}}

typedef enum { 
    GATHER_IDLE, 
    GATHER_ENABLE, 
    GATHER_KEEP, 
    GATHER_ERROR 
} gather_code;

/* FUNCTIONS */

data_t* structureCreate();
void structureToBson(data_t *document, bson_t **bson_document);
void structureDelete(data_t *document);

#endif