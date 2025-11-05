#include <pico/stdlib.h>

#include "ws2812_set_rgb.h"

#include "enum.h"
#include "joint.h"
#include "ros.h"
#include "rcl/logging_rosout.h"

status_t init_lucy(void);
void dump_config(void);
status_t ping_agent(int timeout_ms, int nb_attempts);

/**
 * Global variable to indicate if a connection check is needed
 */
bool NEED_CONNECTION_CHECK = false;

/**
 * Callback function to set the NEED_CONNECTION_CHECK flag
 */
bool need_connection_check_callback(repeating_timer_t *timer) {
  NEED_CONNECTION_CHECK = true;
  return true;
}

/**
 * Check the connection to the ROS2 agent and recreate the node if the connection is lost
 */
static void check_connection()
{
  if (ping_agent(1000, 1) == KO) {
    destroy_node_pico();
    create_node_pico();
  }
}

int main(void) {
  dump_config();
  if (init_lucy() == KO) {
    ws2812_set_rgb(0, 10, 0, 0);
    return KO;
  }
  ws2812_set_rgb(0, 0, 10, 0);
  repeating_timer_t need_connection_check_timer;
  add_repeating_timer_ms(1000, &need_connection_check_callback, NULL, &need_connection_check_timer);

  while (true) {
    rclc_executor_spin_some(&node.executor, RCL_MS_TO_NS(100));
    if (NEED_CONNECTION_CHECK) {
      check_connection();
    }
  }
}