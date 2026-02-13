#pragma once

#include <rcl/subscription.h>
#include <sensor_msgs/msg/joint_state.h>

#include "constant.h"

struct joint_s;
struct board_s;

typedef struct joint_config_s {
  int16_t virtual_pin;
  int16_t physical_pin;
  double servo_type;
  double security_min_angle;
  double security_max_angle;
  double default_angle;

  void (*init_joint)(struct board_s *board, struct joint_s *joint);
  void (*move_joint)(struct board_s *board, struct joint_s *joint);
} joint_config_t;

typedef struct joint_s {
  float angle;
  joint_config_t config;
} joint_t;


extern double joints_angle[NB_JOINTS];
extern rcl_subscription_t joint_subscriber;
extern sensor_msgs__msg__JointState joint_subscriber_data;


void internal_joint_init(struct board_s *board, joint_t *joint);
void internal_joint_move(struct board_s *board, joint_t *joint);

void adafruit_joint_init(struct board_s *board, joint_t *joint);
void adafruit_joint_move(struct board_s *board, joint_t *joint);