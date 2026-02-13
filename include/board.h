#pragma once

#include <sensor_msgs/msg/joint_state.h>
#include <hardware/pwm.h>
#include <hardware/i2c.h>

#include "joint.h"
#include "sensor.h"
#include "constant.h"

struct i2c_pin_s {
  int16_t sda;
  int16_t scl;
  i2c_inst_t *port;
};

struct adafruit_s {
  joint_t joints[NB_ADAFRUIT_JOINTS];
};


struct analog_multiplexer {
  uint addr0_pin;
  uint addr1_pin;
  uint addr2_pin;
  uint shared_pin;
};

struct internal_s {
  struct analog_multiplexer mux;
  sensor_t sensors[NB_INTERNAL_SENSORS];
  pwm_config pwm_config;
  joint_t joints[NB_INTERNAL_JOINTS];
};




union board_pin_u {
  struct i2c_pin_s i2c;
};

union board_data_u {
  struct internal_s internal;
  struct adafruit_s adafruit;
};

typedef struct board_s {
  union board_pin_u pin;
  union board_data_u data;
  void (*init)(struct board_s *board);
  void (*on_joint_subscriber_update)(struct board_s *board, const sensor_msgs__msg__JointState *inputs);
  void (*on_sensor_timer_tick)(struct board_s *board);
  void (*on_uptime_timer_tick)(struct board_s *board);
} board_t;

extern board_t boards[NB_BOARDS];

void internal_init(board_t *board);
void internal_on_joint_subscriber_update(board_t *board, const sensor_msgs__msg__JointState *inputs);
void internal_on_sensor_timer_tick(board_t *board);

void adafruit_init(board_t *board);
void adafruit_on_joint_subscriber_update(board_t *board, const sensor_msgs__msg__JointState *inputs);