#include "gather_can_primary_service.h"

/* INTERNAL VARIABLES AND STRUCTS */

static pthread_t _gather_can_thread;
static pthread_attr_t _gather_can_thread_attr;

/* INTERNAL FUNCTIONS SIGNATURES */

static void* _parseCanMessages(void* args);

/* EXPORTED FUNCTIONS */

void gatherCanPrimaryStartThread(int enabled) {
	pthread_attr_init(&_gather_can_thread_attr);
	pthread_attr_setdetachstate(&_gather_can_thread_attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&_gather_can_thread, &_gather_can_thread_attr, &_parseCanMessages, (void*)((long)enabled));
	pthread_attr_destroy(&_gather_can_thread_attr);
}

void gatherCanPrimaryStopThread() {
	pthread_cancel(_gather_can_thread);
}

/* INTERNAL FUNCTIONS DEFINITIONS */

static void* _parseCanMessages(void* args) {
	// Getting enabled arg
	int enabled = (int)((long)args);

	// Declare used variables
	data_t* document;
	int id;
	char* data;

	while (1) {
		// Read can
		canReadPrimary(&id, &data);

		// Lock document
		pthread_mutex_lock(&condition.structure.threads.data_head_mutex);

		// Create reference to data_head
		document = condition.structure.data_head;

		switch (id) {
			case (ID_SPEED): {
				int count = document->inverters.right.speed_count;
				if (count < document->inverters.right.speed_size) {
					Primary_SPEED* message = (Primary_SPEED*) malloc(sizeof(Primary_SPEED));
					deserialize_Primary_SPEED(data, 8, message);
					
					
					document->inverters.right.speed[count].timestamp = getCurrentTimestamp();
					document->inverters.right.speed[count].value = message->speed;
					++document->inverters.right.speed_count;
				}
				break;
			}
			
			case (ID_IGBT_TEMP): {
				int count = document->inverters.right.temperature_igbt_count;
				if (count < document->inverters.right.temperature_igbt_size) {
					Primary_IGBT_TEMP* message = (Primary_IGBT_TEMP*) malloc(sizeof(Primary_IGBT_TEMP));
					deserialize_Primary_IGBT_TEMP(data, 8, message);
					
					
					document->inverters.right.temperature_igbt[count].timestamp = getCurrentTimestamp();
					document->inverters.right.temperature_igbt[count].value = message->igbt_temp * 2;
					++document->inverters.right.temperature_igbt_count;
				}
				break;
			}
			
			
		}

		// Unlock document
		pthread_mutex_unlock(&condition.structure.threads.data_head_mutex);
	}

	return NULL;
}
