#include "board.h"

#include <hardware/adc.h>

#include "i2c.h"

/* INTERNAL */

void internal_init(board_t *board) {
  { // Initialisation of PWM config
    board->data.internal.pwm_config = pwm_get_default_config();
    pwm_config_set_wrap(&board->data.internal.pwm_config, 20000);
    pwm_config_set_clkdiv(&board->data.internal.pwm_config, 125.f);
  }

  { // Initialisation of analog multiplexer
    board->data.internal.mux.addr0_pin = 22;
    board->data.internal.mux.addr1_pin = 24;
    board->data.internal.mux.addr2_pin = 25;
    board->data.internal.mux.shared_pin = 29;

    gpio_init(board->data.internal.mux.addr0_pin);
    gpio_init(board->data.internal.mux.addr1_pin);
    gpio_init(board->data.internal.mux.addr2_pin);
    gpio_init(board->data.internal.mux.shared_pin);

    gpio_set_dir(board->data.internal.mux.addr0_pin, GPIO_OUT);
    gpio_set_dir(board->data.internal.mux.addr1_pin, GPIO_OUT);
    gpio_set_dir(board->data.internal.mux.addr2_pin, GPIO_OUT);
    gpio_set_pulls(board->data.internal.mux.shared_pin, false, true);
  }

  { // Initialisation of internal joints
    for (int16_t i = 0; i < NB_INTERNAL_JOINTS; i++) {
      if (board->data.internal.joints[i].config.init_joint != NULL) {
        board->data.internal.joints[i].config.init_joint(board, &board->data.internal.joints[i]);
      }
    }
  }

  { // Initialisation of internal sensors
    for (int16_t i = 0; i < NB_INTERNAL_SENSORS; i++) {
      if (board->data.internal.sensors[i].config.init_sensor != NULL) {
        board->data.internal.sensors[i].config.init_sensor(board, &board->data.internal.sensors[i]);
      }
    }
  }
}

void internal_on_joint_subscriber_update(board_t *board, const sensor_msgs__msg__JointState *inputs) {
  double new_angle;

  for (int i = 0; i < NB_INTERNAL_JOINTS; i++) {
    joint_t *joint = &board->data.internal.joints[i];
    if (joint->config.move_joint != NULL) {
      new_angle = inputs->position.data[joint->config.virtual_pin];
      joint->angle = new_angle;
      joint->config.move_joint(board, joint);
    }
  }
}

void internal_on_sensor_timer_tick(board_t *board) {
  adc_select_input(3);
  for (int i = 0; i < NB_INTERNAL_SENSORS; i++) {
    sensor_t *sensor = &board->data.internal.sensors[i];
    if (sensor->config.read_sensor) {
      float value = sensor->config.read_sensor(board, sensor);
      sensors_value[i] = value;
    }
  }
}

/* ADAFRUIT */



void pca_init() {
  pca_write_reg(i2c0, PCA_ADDR, REG_MODE1, 0x00);
  sleep_ms(1);

  pca_write_reg(i2c0, PCA_ADDR, REG_MODE1, 0x10);
  sleep_ms(1);

  int prescale_val = (int)(25000000.f / (4096.f * 50.f)) - 1;
  pca_write_reg(i2c0, PCA_ADDR, REG_PRESCALE, prescale_val);
  sleep_ms(1);

  pca_write_reg(i2c0, PCA_ADDR, REG_MODE1, 0x00);
  sleep_ms(1);

  pca_write_reg(i2c0, PCA_ADDR, REG_MODE1, 0x80);
  sleep_ms(1);

  pca_write_reg(i2c0, PCA_ADDR, REG_MODE1, 0x21);
  sleep_ms(1);
}

void adafruit_init(board_t *board) {
  i2c_init(board->pin.i2c.port, I2C_FREQUENCY);
  gpio_set_function(board->pin.i2c.sda, GPIO_FUNC_I2C);
  gpio_set_function(board->pin.i2c.scl, GPIO_FUNC_I2C);
  gpio_pull_up(board->pin.i2c.sda);
  gpio_pull_up(board->pin.i2c.scl);
  pca_init();

  for (int16_t i = 0; i < NB_ADAFRUIT_JOINTS; i++) {
    if (board->data.adafruit.joints[i].config.init_joint != NULL) {
      board->data.adafruit.joints[i].config.init_joint(board, &board->data.adafruit.joints[i]);
    }
  }
}

void adafruit_on_joint_subscriber_update(board_t *board, const sensor_msgs__msg__JointState *inputs) {
  double new_angle;

  for (int i = 0; i < NB_ADAFRUIT_JOINTS; i++) {
    if (board->data.adafruit.joints[i].config.move_joint != NULL) {
      new_angle = inputs->position.data[board->data.internal.joints[i].config.virtual_pin];
      board->data.adafruit.joints[i].angle = new_angle;
      board->data.adafruit.joints[i].config.move_joint(board, &board->data.adafruit.joints[i]);
    }
  }
}



board_t boards[NB_BOARDS];