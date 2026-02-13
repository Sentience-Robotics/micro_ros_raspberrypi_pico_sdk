#include "joint.h"

#include <hardware/gpio.h>

#include "i2c.h"
#include "board.h"
#include "constant.h"

double joints_angle[NB_JOINTS] = {};
rcl_subscription_t joint_subscriber = {};
sensor_msgs__msg__JointState joint_subscriber_data = {
  .position = {
    .data = joints_angle,
    .size = NB_JOINTS,
    .capacity = NB_JOINTS
  }
};

void internal_joint_init(board_t *board, joint_t *joint) {
  int sliceNum = pwm_gpio_to_slice_num(joint->config.physical_pin);

  gpio_set_function(joint->config.physical_pin, GPIO_FUNC_PWM);
  pwm_init(sliceNum, &board->data.internal.pwm_config, true);
}

void internal_joint_move(board_t *board, joint_t *joint) {
  double angle = CLAMP(joint->angle, joint->config.security_min_angle, joint->config.security_max_angle);
  double us = map(angle, 0, joint->config.servo_type, MIN_PULSE, MAX_PULSE);

  pwm_set_gpio_level(joint->config.physical_pin, us);
}

void adafruit_joint_init(board_t *board, joint_t *joint) {
  // Nothing to do here for now
}

void adafruit_joint_move(board_t *board, joint_t *joint) {
  double angle = CLAMP(joint->angle, joint->config.security_min_angle, joint->config.security_max_angle);

  double off_tick = map(angle, 0, joint->config.servo_type, MIN_PULSE, MAX_PULSE) / (20000.f / 4096.f);
  int on_tick = 0;

  uint8_t base_reg = REG_LED0_ON_L + (joint->config.physical_pin * 4);
  pca_write_reg(i2c0, PCA_ADDR, base_reg, (int)on_tick & 0xFF);
  pca_write_reg(i2c0, PCA_ADDR, base_reg + 1, ((int)on_tick >> 8) & 0xFF);
  pca_write_reg(i2c0, PCA_ADDR, base_reg + 2, (int)off_tick & 0xFF);
  pca_write_reg(i2c0, PCA_ADDR, base_reg + 3, ((int)off_tick >> 8) & 0xFF);

}