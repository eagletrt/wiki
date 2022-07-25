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
			case (ID_MOTORS_TEMP): {
				int count = document->inverters.right.temperature_motors_count;
				if (count < document->inverters.right.temperature_motors_size) {
					Secondary_MOTORS_TEMP* message = (Secondary_MOTORS_TEMP*) malloc(sizeof(Secondary_MOTORS_TEMP));
					deserialize_Secondary_MOTORS_TEMP(data, 8, message);
					
					double adjustment = 3.1415;
					double adjustedMotors = message->motors + adjustment;
					
					document->inverters.right.temperature_motors[count].timestamp = getCurrentTimestamp();
					document->inverters.right.temperature_motors[count].value = adjustedMotors + message->avg;
					++document->inverters.right.temperature_motors_count;
				}
				break;
			}
			
			case (ID_IMU_GYRO): {
				int count = document->imu_gyro_count;
				if (count < document->imu_gyro_size) {
					Secondary_IMU_GYRO* message = (Secondary_IMU_GYRO*) malloc(sizeof(Secondary_IMU_GYRO));
					deserialize_Secondary_IMU_GYRO(data, 8, message);
					
					
					document->imu_gyro[count].timestamp = getCurrentTimestamp();
					document->imu_gyro[count].value.x = message->x + message->scale;
					document->imu_gyro[count].value.y = message->y + message->scale;
					document->imu_gyro[count].value.z = message->z + message->scale;
					++document->imu_gyro_count;
				}
				break;
			}
			
			
		}

		// Unlock document
		pthread_mutex_unlock(&condition.structure.threads.data_head_mutex);
	}

	return NULL;
}
