#include ".bin/structure_type.h"

void structureToBson(data_t *data, bson_t** bson_document) {
	*bson_document = bson_new();
	bson_t *children = (bson_t*)malloc(sizeof(bson_t) * 6);
	BSON_APPEND_INT32(*bson_document, "id", data->id);
	BSON_APPEND_INT64(*bson_document, "timestamp", data->timestamp);
	BSON_APPEND_UTF8(*bson_document, "sessionName", data->sessionName);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "inverters", &children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(&children[0], "right", &children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "speed", &children[2]);
	for (int i = 0; i < (data->inverters.right.speed_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.right.speed[i].timestamp);
		BSON_APPEND_INT32(&children[3], "value", data->inverters.right.speed[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "temperature_igbt", &children[2]);
	for (int i = 0; i < (data->inverters.right.temperature_igbt_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.right.temperature_igbt[i].timestamp);
		BSON_APPEND_INT32(&children[3], "value", data->inverters.right.temperature_igbt[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "temperature_motors", &children[2]);
	for (int i = 0; i < (data->inverters.right.temperature_motors_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.right.temperature_motors[i].timestamp);
		BSON_APPEND_INT32(&children[3], "value", data->inverters.right.temperature_motors[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	bson_append_document_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_DOCUMENT_BEGIN(&children[0], "left", &children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "speed", &children[2]);
	for (int i = 0; i < (data->inverters.left.speed_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.left.speed[i].timestamp);
		BSON_APPEND_INT32(&children[3], "value", data->inverters.left.speed[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "temperature_igbt", &children[2]);
	for (int i = 0; i < (data->inverters.left.temperature_igbt_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.left.temperature_igbt[i].timestamp);
		BSON_APPEND_INT32(&children[3], "value", data->inverters.left.temperature_igbt[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "temperature_motors", &children[2]);
	for (int i = 0; i < (data->inverters.left.temperature_motors_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->inverters.left.temperature_motors[i].timestamp);
		BSON_APPEND_INT32(&children[3], "value", data->inverters.left.temperature_motors[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	bson_append_document_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "bms_hv", &children[0]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "temperature", &children[1]);
	for (int i = 0; i < (data->bms_hv.temperature_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_hv.temperature[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "max", data->bms_hv.temperature[i].value.max);
		BSON_APPEND_DOUBLE(&children[3], "min", data->bms_hv.temperature[i].value.min);
		BSON_APPEND_DOUBLE(&children[3], "average", data->bms_hv.temperature[i].value.average);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "voltage", &children[1]);
	for (int i = 0; i < (data->bms_hv.voltage_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_hv.voltage[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "max", data->bms_hv.voltage[i].value.max);
		BSON_APPEND_DOUBLE(&children[3], "min", data->bms_hv.voltage[i].value.min);
		BSON_APPEND_DOUBLE(&children[3], "total", data->bms_hv.voltage[i].value.total);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "current", &children[1]);
	for (int i = 0; i < (data->bms_hv.current_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_hv.current[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "current", data->bms_hv.current[i].value.current);
		BSON_APPEND_DOUBLE(&children[3], "pow", data->bms_hv.current[i].value.pow);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "errors", &children[1]);
	for (int i = 0; i < (data->bms_hv.errors_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_hv.errors[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_INT32(&children[3], "fault_id", data->bms_hv.errors[i].value.fault_id);
		BSON_APPEND_INT32(&children[3], "fault_index", data->bms_hv.errors[i].value.fault_index);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "warnings", &children[1]);
	for (int i = 0; i < (data->bms_hv.warnings_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_hv.warnings[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_INT32(&children[3], "fault_id", data->bms_hv.warnings[i].value.fault_id);
		BSON_APPEND_INT32(&children[3], "fault_index", data->bms_hv.warnings[i].value.fault_index);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "bms_lv", &children[0]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "values", &children[1]);
	for (int i = 0; i < (data->bms_lv.values_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_lv.values[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "voltage", data->bms_lv.values[i].value.voltage);
		BSON_APPEND_DOUBLE(&children[3], "temperature", data->bms_lv.values[i].value.temperature);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "errors", &children[1]);
	for (int i = 0; i < (data->bms_lv.errors_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->bms_lv.errors[i].timestamp);
		BSON_APPEND_INT32(&children[2], "value", data->bms_lv.errors[i].value);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "gps", &children[0]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "new", &children[1]);
	for (int i = 0; i < (data->gps.new_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->gps.new[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_DOUBLE(&children[3], "latitude_GGA_safe", data->gps.new[i].value.latitude_GGA_safe);
		BSON_APPEND_DOUBLE(&children[3], "longitude_GGA_safe", data->gps.new[i].value.longitude_GGA_safe);
		BSON_APPEND_DOUBLE(&children[3], "latitude_GGA", data->gps.new[i].value.latitude_GGA);
		BSON_APPEND_DOUBLE(&children[3], "longitude_GGA", data->gps.new[i].value.longitude_GGA);
		BSON_APPEND_DOUBLE(&children[3], "altitude_GGA", data->gps.new[i].value.altitude_GGA);
		BSON_APPEND_UTF8(&children[3], "ns_indicator_GGA", data->gps.new[i].value.ns_indicator_GGA);
		BSON_APPEND_UTF8(&children[3], "ew_indicator_GGA", data->gps.new[i].value.ew_indicator_GGA);
		BSON_APPEND_UTF8(&children[3], "utc_time_GGA", data->gps.new[i].value.utc_time_GGA);
		BSON_APPEND_DOUBLE(&children[3], "latitude_GLL", data->gps.new[i].value.latitude_GLL);
		BSON_APPEND_DOUBLE(&children[3], "longitude_GLL", data->gps.new[i].value.longitude_GLL);
		BSON_APPEND_UTF8(&children[3], "ns_indicator_GLL", data->gps.new[i].value.ns_indicator_GLL);
		BSON_APPEND_UTF8(&children[3], "ew_indicator_GLL", data->gps.new[i].value.ew_indicator_GLL);
		BSON_APPEND_UTF8(&children[3], "utc_time_GLL", data->gps.new[i].value.utc_time_GLL);
		BSON_APPEND_DOUBLE(&children[3], "ground_speed_knots_VTG", data->gps.new[i].value.ground_speed_knots_VTG);
		BSON_APPEND_DOUBLE(&children[3], "ground_speed_human_VTG", data->gps.new[i].value.ground_speed_human_VTG);
		BSON_APPEND_DOUBLE(&children[3], "latitude_RMC", data->gps.new[i].value.latitude_RMC);
		BSON_APPEND_DOUBLE(&children[3], "longitude_RMC", data->gps.new[i].value.longitude_RMC);
		BSON_APPEND_UTF8(&children[3], "ns_indicator_RMC", data->gps.new[i].value.ns_indicator_RMC);
		BSON_APPEND_UTF8(&children[3], "ew_indicator_RMC", data->gps.new[i].value.ew_indicator_RMC);
		BSON_APPEND_UTF8(&children[3], "utc_time_RMC", data->gps.new[i].value.utc_time_RMC);
		BSON_APPEND_UTF8(&children[3], "date_RMC", data->gps.new[i].value.date_RMC);
		BSON_APPEND_DOUBLE(&children[3], "ground_speed_knots_RMC", data->gps.new[i].value.ground_speed_knots_RMC);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_DOCUMENT_BEGIN(&children[0], "old", &children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "location", &children[2]);
	for (int i = 0; i < (data->gps.old.location_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->gps.old.location[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_DOUBLE(&children[4], "latitude_m", data->gps.old.location[i].value.latitude_m);
		BSON_APPEND_INT32(&children[4], "latitude_o", data->gps.old.location[i].value.latitude_o);
		BSON_APPEND_DOUBLE(&children[4], "longitude_m", data->gps.old.location[i].value.longitude_m);
		BSON_APPEND_INT32(&children[4], "longitude_o", data->gps.old.location[i].value.longitude_o);
		BSON_APPEND_DOUBLE(&children[4], "speed", data->gps.old.location[i].value.speed);
		BSON_APPEND_DOUBLE(&children[4], "altitude", data->gps.old.location[i].value.altitude);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "time", &children[2]);
	for (int i = 0; i < (data->gps.old.time_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->gps.old.time[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[3], "value", &children[4]);
		BSON_APPEND_INT32(&children[4], "hours", data->gps.old.time[i].value.hours);
		BSON_APPEND_INT32(&children[4], "minutes", data->gps.old.time[i].value.minutes);
		BSON_APPEND_INT32(&children[4], "seconds", data->gps.old.time[i].value.seconds);
		bson_append_document_end(&children[3], &children[4]);
		bson_destroy(&children[4]);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	BSON_APPEND_ARRAY_BEGIN(&children[1], "true_track_mode", &children[2]);
	for (int i = 0; i < (data->gps.old.true_track_mode_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "0", &children[3]);
		BSON_APPEND_INT64(&children[3], "timestamp", data->gps.old.true_track_mode[i].timestamp);
		BSON_APPEND_INT32(&children[3], "value", data->gps.old.true_track_mode[i].value);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
	}
	bson_append_array_end(&children[1], &children[2]);
	bson_destroy(&children[2]);
	bson_append_document_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_ARRAY_BEGIN(*bson_document, "imu_gyro", &children[0]);
	for (int i = 0; i < (data->imu_gyro_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[0], "0", &children[1]);
		BSON_APPEND_INT64(&children[1], "timestamp", data->imu_gyro[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "value", &children[2]);
		BSON_APPEND_DOUBLE(&children[2], "x", data->imu_gyro[i].value.x);
		BSON_APPEND_DOUBLE(&children[2], "y", data->imu_gyro[i].value.y);
		BSON_APPEND_DOUBLE(&children[2], "z", data->imu_gyro[i].value.z);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
		bson_append_document_end(&children[0], &children[1]);
		bson_destroy(&children[1]);
	}
	bson_append_array_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_ARRAY_BEGIN(*bson_document, "imu_accel", &children[0]);
	for (int i = 0; i < (data->imu_accel_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[0], "0", &children[1]);
		BSON_APPEND_INT64(&children[1], "timestamp", data->imu_accel[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "value", &children[2]);
		BSON_APPEND_DOUBLE(&children[2], "x", data->imu_accel[i].value.x);
		BSON_APPEND_DOUBLE(&children[2], "y", data->imu_accel[i].value.y);
		BSON_APPEND_DOUBLE(&children[2], "z", data->imu_accel[i].value.z);
		BSON_APPEND_DOUBLE(&children[2], "scale", data->imu_accel[i].value.scale);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
		bson_append_document_end(&children[0], &children[1]);
		bson_destroy(&children[1]);
	}
	bson_append_array_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_ARRAY_BEGIN(*bson_document, "front_wheels_encoder", &children[0]);
	for (int i = 0; i < (data->front_wheels_encoder_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[0], "0", &children[1]);
		BSON_APPEND_INT64(&children[1], "timestamp", data->front_wheels_encoder[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "value", &children[2]);
		BSON_APPEND_DOUBLE(&children[2], "speed", data->front_wheels_encoder[i].value.speed);
		BSON_APPEND_DOUBLE(&children[2], "speedms", data->front_wheels_encoder[i].value.speedms);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
		bson_append_document_end(&children[0], &children[1]);
		bson_destroy(&children[1]);
	}
	bson_append_array_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_ARRAY_BEGIN(*bson_document, "distance", &children[0]);
	for (int i = 0; i < (data->distance_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[0], "0", &children[1]);
		BSON_APPEND_INT64(&children[1], "timestamp", data->distance[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "value", &children[2]);
		BSON_APPEND_DOUBLE(&children[2], "meters", data->distance[i].value.meters);
		BSON_APPEND_DOUBLE(&children[2], "rotations", data->distance[i].value.rotations);
		BSON_APPEND_DOUBLE(&children[2], "angle", data->distance[i].value.angle);
		BSON_APPEND_DOUBLE(&children[2], "clock_period", data->distance[i].value.clock_period);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
		bson_append_document_end(&children[0], &children[1]);
		bson_destroy(&children[1]);
	}
	bson_append_array_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_ARRAY_BEGIN(*bson_document, "throttle", &children[0]);
	for (int i = 0; i < (data->throttle_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[0], "0", &children[1]);
		BSON_APPEND_INT64(&children[1], "timestamp", data->throttle[i].timestamp);
		BSON_APPEND_DOUBLE(&children[1], "value", data->throttle[i].value);
		bson_append_document_end(&children[0], &children[1]);
		bson_destroy(&children[1]);
	}
	bson_append_array_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_ARRAY_BEGIN(*bson_document, "brake", &children[0]);
	for (int i = 0; i < (data->brake_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[0], "0", &children[1]);
		BSON_APPEND_INT64(&children[1], "timestamp", data->brake[i].timestamp);
		BSON_APPEND_DOUBLE(&children[1], "value", data->brake[i].value);
		bson_append_document_end(&children[0], &children[1]);
		bson_destroy(&children[1]);
	}
	bson_append_array_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	BSON_APPEND_DOCUMENT_BEGIN(*bson_document, "steering_wheel", &children[0]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "encoder", &children[1]);
	for (int i = 0; i < (data->steering_wheel.encoder_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->steering_wheel.encoder[i].timestamp);
		BSON_APPEND_DOUBLE(&children[2], "value", data->steering_wheel.encoder[i].value);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_ARRAY_BEGIN(&children[0], "gears", &children[1]);
	for (int i = 0; i < (data->steering_wheel.gears_count); i++)
	{
		BSON_APPEND_DOCUMENT_BEGIN(&children[1], "0", &children[2]);
		BSON_APPEND_INT64(&children[2], "timestamp", data->steering_wheel.gears[i].timestamp);
		BSON_APPEND_DOCUMENT_BEGIN(&children[2], "value", &children[3]);
		BSON_APPEND_INT32(&children[3], "control", data->steering_wheel.gears[i].value.control);
		BSON_APPEND_INT32(&children[3], "cooling", data->steering_wheel.gears[i].value.cooling);
		BSON_APPEND_INT32(&children[3], "map", data->steering_wheel.gears[i].value.map);
		bson_append_document_end(&children[2], &children[3]);
		bson_destroy(&children[3]);
		bson_append_document_end(&children[1], &children[2]);
		bson_destroy(&children[2]);
	}
	bson_append_array_end(&children[0], &children[1]);
	bson_destroy(&children[1]);
	BSON_APPEND_INT32(&children[0], "marker", data->steering_wheel.marker);
	bson_append_document_end(*bson_document, &children[0]);
	bson_destroy(&children[0]);
	
}