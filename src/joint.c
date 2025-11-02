#include "joint.h"
#include "util.h"
#include "board.h"
#include "ws2812_set_rgb.h"

double joints_angle[NB_JOINTS] = {};

rcl_subscription_t joint_subscriber = {};
sensor_msgs__msg__JointState joint_subscriber_data = {};

rcl_subscription_t joint_config_subscriber = {};

void internal_joint_init(board_t *board, joint_t *joint) {
  int sliceNum = pwm_gpio_to_slice_num(joint->config.physical_pin - 1);

  gpio_set_function(joint->config.physical_pin - 1, GPIO_FUNC_PWM);
  pwm_init(sliceNum, &board->data.internal.pwm_config, true);
}

void internal_joint_move(board_t *board, joint_t *joint) {
  double angle = CLAMP(joint->angle, joint->config.security_min_angle, joint->config.security_max_angle);
  double us = map(angle, 0, joint->config.servo_type, MIN_PULSE, MAX_PULSE);
  ws2812_set_rgb(4, us / 10, 0, 0);
  pwm_set_gpio_level(joint->config.physical_pin - 1, us); // Pin 1 on the board is GPIO 0
}
