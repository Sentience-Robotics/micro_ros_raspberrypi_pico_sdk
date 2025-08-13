#include <stdio.h>
#include <pico/stdlib.h>

#include "ws2812.h"
#include "ws2812_set_rgb.h"

#include "enum.h"
#include "constant.h"
#include "joint.h"
#include "pwm.h"
#include "ros.h"

static status_t init_led(void) {
  ws2812_init(pio1, DEBUG_LED_PIN, FREQ_HZ);
  ws2812_clear();
  ws2812_set_rgb(0, 10, 10, 0);
  return OK;
}

static status_t init_stdio(void) {
  stdio_init_all();
  while (!stdio_usb_connected()) {
    sleep_ms(100);
  }
  return OK;
}

static status_t init_hardware(void) {
  init_pwm();
  for (int16_t pin = 0; pin < NB_JOINTS; pin++) {
    if (joints[pin].config.init_callback != NULL) {
      joints[pin].config.init_callback(&joints[pin]);
    }
  }
  return OK;
}

status_t init_lucy(void) {
  init_led();
  init_stdio();
  init_hardware();
  return init_ros_pico();
}
