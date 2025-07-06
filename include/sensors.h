#pragma once

#include "constant.h"

typedef struct sensor_config_s {
  uint8_t pin;
} sensor_config_t;

typedef struct sensor_s {
  unsigned double value;
  const sensor_config_t config;
} sensor_t;

extern sensor_t sensors[NB_SENSORS];
