#include "joint.h"
#include "pwm.h"
#include "util.h"

#define DefineNothing(PIN) \
  [PIN] = { \
    .config = {PIN, 0, 0, 0, 0, 0, NULL, NULL}, \
  }

/* Physical min and max of servo are the same */
#define DefineBasicServo(PIN, PMIN, PMAX, DEFAULT_ANGLE) \
  [PIN] = { \
    .angle = DEFAULT_ANGLE, \
    .config = {PIN, PMIN, PMAX, PMIN, PMAX, DEFAULT_ANGLE, &default_joint_init, &default_joint_move}, \
  },

/* Define every element of the joint */
#define DefineFullServo(PIN, PMIN, PMAX, MIN, MAX, DEFAULT_ANGLE, INIT_CALLBACK, MOVE_CALLBACK) \
  { \
    .angle = DEFAULT_ANGLE, \
    .config = {PIN, PMIN, PMAX, MIN, MAX, DEFAULT_ANGLE, JOINT_INIT_CALLBACK, JOINT_MOVE_CALLBACK} \
  },

joint_t joints[NB_JOINTS] = {
#include "../config/joint_mapping.h"
};
double joints_angle[NB_JOINTS] = {};

rcl_subscription_t joint_subscriber = {};
sensor_msgs__msg__JointState joint_subscriber_data = {};

rcl_subscription_t joint_config_subscriber = {};

void default_joint_init(joint_t *joint) {
  init_pwm_port(joint->config.pin);
}

void default_joint_move(joint_t *joint) {
  double us = map(joint->angle, joint->config.physical_min_angle, joint->config.physical_max_angle, MIN_PULSE, MAX_PULSE);
  pwm_set_gpio_level(joint->config.pin, us);
}
