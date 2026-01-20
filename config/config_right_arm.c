#include "constant.h"
#include "joint.h"
#include "board.h"

void dump_config(void) {
  memset(boards, 0, sizeof(boards));

  // Setup internal board
  board_t *board = &boards[0];
  board->init = &internal_init;
  board->on_joint_subscriber_update = &internal_on_joint_subscriber_update;

  // Setup servo

  joint_t *joint = board->data.internal.joints;

  // Shoulder Yaw
  joint->config.virtual_pin = 0;
  joint->config.physical_pin = INTERNAL_SERVO_10;
  joint->config.servo_type = SERVO_TYPE_270;
  joint->config.security_min_angle = 170; // 140
  joint->config.security_max_angle = 200; // 230
  joint->config.default_angle = 180;
  joint->config.init_joint = &internal_joint_init;
  joint->config.move_joint = &internal_joint_move;
  joint++;

  // Shoulder Roll
  joint->config.virtual_pin = 1;
  joint->config.physical_pin = INTERNAL_SERVO_11;
  joint->config.servo_type = SERVO_TYPE_270;
  joint->config.security_min_angle = 140; //90
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 145;
  joint->config.init_joint = &internal_joint_init;
  joint->config.move_joint = &internal_joint_move;
  joint++;

  // Elbow
  joint->config.virtual_pin = 2;
  joint->config.physical_pin = INTERNAL_SERVO_12;
  joint->config.servo_type = SERVO_TYPE_270;
  joint->config.security_min_angle = 100; // 40 min
  joint->config.security_max_angle = 125;
  joint->config.default_angle = 120;
  joint->config.init_joint = &internal_joint_init;
  joint->config.move_joint = &internal_joint_move;
  joint++;

  // Wrist
  joint->config.virtual_pin = 3;
  joint->config.physical_pin = INTERNAL_SERVO_13;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_joint = &internal_joint_init;
  joint->config.move_joint = &internal_joint_move;
  joint++;

  // Thumb
  joint->config.virtual_pin = 4;
  joint->config.physical_pin = INTERNAL_SERVO_14;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_joint = &internal_joint_init;
  joint->config.move_joint = &internal_joint_move;
  joint++;

  // Index
  joint->config.virtual_pin = 5;
  joint->config.physical_pin = INTERNAL_SERVO_15;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_joint = &internal_joint_init;
  joint->config.move_joint = &internal_joint_move;
  joint++;

  // Middle
  joint->config.virtual_pin = 6;
  joint->config.physical_pin = INTERNAL_SERVO_16;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_joint = &internal_joint_init;
  joint->config.move_joint = &internal_joint_move;
  joint++;

  // Ring
  joint->config.virtual_pin = 7;
  joint->config.physical_pin = INTERNAL_SERVO_17;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_joint = &internal_joint_init;
  joint->config.move_joint = &internal_joint_move;
  joint++;

  // Pinky
  joint->config.virtual_pin = 8;
  joint->config.physical_pin = INTERNAL_SERVO_18;
  joint->config.servo_type = SERVO_TYPE_300;
  joint->config.security_min_angle = 0;
  joint->config.security_max_angle = 150;
  joint->config.default_angle = 50;
  joint->config.init_joint = &internal_joint_init;
  joint->config.move_joint = &internal_joint_move;
  joint++;
}
