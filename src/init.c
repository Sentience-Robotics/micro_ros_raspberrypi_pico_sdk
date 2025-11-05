#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/i2c.h>

#include "ws2812.h"
#include "ws2812_set_rgb.h"

#include "board.h"
#include "enum.h"
#include "constant.h"
#include "joint.h"
#include "ros.h"
#include "pico_uart_transports/pico_uart_transports.h"
#include "rmw_microros/custom_transport.h"

status_t init_led(void) {
  ws2812_init(pio1, DEBUG_LED_PIN, FREQ_HZ);
  ws2812_clear();
  ws2812_set_rgb(0, 10, 10, 0);
  return OK;
}

status_t init_stdio(void) {
  stdio_init_all();
  while (!stdio_usb_connected()) {
    sleep_ms(100);
  }
  return OK;
}

status_t init_board(void) {
  for (int i = 0; i < NB_BOARDS; i++) {
    if (boards[i].init != NULL) {
      boards[i].init(&boards[i]);
    }
  }
  return OK;
}

status_t init_lucy(void) {
  init_led();
  init_stdio();
  init_board();
  rmw_uros_set_custom_transport(true, NULL, &pico_serial_transport_open, &pico_serial_transport_close, &pico_serial_transport_write, &pico_serial_transport_read);
  return create_node_pico();;
}
