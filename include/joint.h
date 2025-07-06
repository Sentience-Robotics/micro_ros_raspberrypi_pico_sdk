#pragma once

#include "constant.h"
#include <rclc/rclc.h>
#include <rclc/types.h>
#include <rclc/subscription.h>

#include <sensor_msgs/msg/joint_state.h>

struct joint_s;

typedef struct joint_config_s {
  int8_t pin;
  double physical_min_angle;
  double physical_max_angle;
  double min_angle;
  double max_angle;
  double default_angle;

  void (*init_callback)(struct joint_s *joint);
  void (*move_callback)(struct joint_s *joint);
} joint_config_t;

typedef struct joint_s {
  double angle;
  joint_config_t config;
} joint_t;

extern joint_t joints[NB_JOINTS];
extern double joints_angle[NB_JOINTS];

extern rcl_subscription_t joint_subscriber;
extern sensor_msgs__msg__JointState joint_subscriber_data;

void default_joint_init(joint_t *joint);
void default_joint_move_pin(joint_t *joint, int pin);
void default_joint_move(joint_t *joint);
