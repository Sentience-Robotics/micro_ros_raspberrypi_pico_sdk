#include <pico/stdlib.h>
#include <pico/time.h>
#include "ws2812_set_rgb.h"
#include "enum.h"
#include "ros.h"
#include <rclc/types.h>
#include <std_msgs/msg/string.h>
#include <rmw_microros/rmw_microros.h>
#include <rmw/rmw.h>
#include <rclc/publisher.h>
#include "constant.h"
#include "pico_uart_transports/pico_uart_transports.h"
#include "joint.h"
#include "ros.h"

status_t init_lucy(void);
void dump_config(void);
status_t ping_agent(int timeout_ms, int nb_attempts);

bool IS_RUNNING = true;

/* MICRO-ROS AGENT */


static void check_connection(uint64_t uptime)
{
  status_t status;
  if (ping_agent(1000, 1) == KO) {
    if (CONNECTION_STATUS == OK) {
      destroy_node_pico();
    }
    ws2812_set_rgb(5, (uptime % 2) * 10, 0, 0);
    CONNECTION_STATUS = KO;
  } else {
    if (CONNECTION_STATUS == KO) {
      create_node_pico();
    }
    ws2812_set_rgb(5, 0, (uptime % 2) * 10, 0);
    CONNECTION_STATUS = OK;
  }
}


int main(void) {
  absolute_time_t time;
  dump_config();
  ws2812_set_rgb(0, 10, 10, 0);
  if (init_lucy() == KO) {
    ws2812_set_rgb(0, 10, 0, 0);
    return KO;
  }
  ws2812_set_rgb(0, 0, 10, 0);
  check_connection(0);

  while (IS_RUNNING) {
    time = get_absolute_time();
    uint64_t uptime = to_us_since_boot(time);
    if (uptime % 1000 == 0) {
      check_connection(uptime);
    }
    rclc_executor_spin_some(&node.executor, RCL_MS_TO_NS(100));
  }
  rclc_executor_fini(&node.executor);
  return 0;
}
