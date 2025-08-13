#include <pico/stdlib.h>

#include "ws2812_set_rgb.h"

#include "enum.h"
#include "ros.h"

status_t init_lucy(void);

int main(void) {
  if (init_lucy() == KO) {
    ws2812_set_rgb(0, 10, 0, 0);
    return KO;
  }
  ws2812_set_rgb(0, 0, 10, 0);

  while (true) {
    rclc_executor_spin_some(&node.executor, RCL_MS_TO_NS(100));
  }
  rclc_executor_fini(&node.executor);
  return 0;
}
