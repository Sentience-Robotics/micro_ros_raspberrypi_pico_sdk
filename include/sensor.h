#pragma once

#include <rcl/publisher.h>
#include <lucy_msgs/msg/raw_sensor.h>

#include "constant.h"

struct sensor_s;
struct board_s;

typedef struct sensor_config_s {
  int16_t virtual_pin;
  int16_t physical_pin;

  void (*init_sensor)(struct board_s *board, struct sensor_s *sensor);
  float (*read_sensor)(struct board_s *board, struct sensor_s *sensor);
} sensor_config_t;

typedef struct sensor_s {
  float value;
  sensor_config_t config;
} sensor_t;

void internal_sensor_init(struct board_s *board, sensor_t *sensor);
float internal_sensor_read(struct board_s *board, sensor_t *sensor);

extern float sensors_value[NB_SENSORS];
extern rcl_publisher_t sensor_publisher;
extern lucy_msgs__msg__RawSensor sensor_publisher_data;