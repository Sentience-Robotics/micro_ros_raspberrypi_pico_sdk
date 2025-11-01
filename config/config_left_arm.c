#include "constant.h"
#include "joint.h"
#include "board.h"

void dump_config(void) {
  memset(boards, 0, sizeof(boards));

  // Setup internal board
  board_t *board = &boards[0];
  board->init = &internal_init;
  board->joint_update = &internal_joint_update;

  // Setup servo

  joint_t *joint = board->data.internal.joints;

  // Shoulder Yaw
  joint->config.virtual_pin = 0;
  joint->config.physical_pin = 10;
  joint->config.servo_type = SERVO_TYPE_270;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 270;
  joint->config.default_angle = 135;
  joint->config.init_callback = &internal_joint_init;
  joint->config.move_callback = &internal_joint_move;
  joint++;

  // Shoulder Roll
  joint->config.virtual_pin = 1;
  joint->config.physical_pin = 11;
  joint->config.servo_type = SERVO_TYPE_270;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 270;
  joint->config.default_angle = 135;
  joint->config.init_callback = &internal_joint_init;
  joint->config.move_callback = &internal_joint_move;
  joint++;

  // Elbow
  joint->config.virtual_pin = 2;
  joint->config.physical_pin = 12;
  joint->config.servo_type = SERVO_TYPE_270;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 270;
  joint->config.default_angle = 90;
  joint->config.init_callback = &internal_joint_init;
  joint->config.move_callback = &internal_joint_move;
  joint++;

  // Wrist
  joint->config.virtual_pin = 3;
  joint->config.physical_pin = 13;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_callback = &internal_joint_init;
  joint->config.move_callback = &internal_joint_move;
  joint++;

  // Thumb
  joint->config.virtual_pin = 4;
  joint->config.physical_pin = 14;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_callback = &internal_joint_init;
  joint->config.move_callback = &internal_joint_move;
  joint++;

  // Index
  joint->config.virtual_pin = 5;
  joint->config.physical_pin = 15;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_callback = &internal_joint_init;
  joint->config.move_callback = &internal_joint_move;
  joint++;

  // Middle
  joint->config.virtual_pin = 6;
  joint->config.physical_pin = 16;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_callback = &internal_joint_init;
  joint->config.move_callback = &internal_joint_move;
  joint++;

  // Ring
  joint->config.virtual_pin = 7;
  joint->config.physical_pin = 17;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_callback = &internal_joint_init;
  joint->config.move_callback = &internal_joint_move;
  joint++;

  // Pinky
  joint->config.virtual_pin = 8;
  joint->config.physical_pin = 18;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_callback = &internal_joint_init;
  joint->config.move_callback = &internal_joint_move;
  joint++;
}
