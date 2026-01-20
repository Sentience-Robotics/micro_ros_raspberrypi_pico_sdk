#pragma once

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include "enum.h"

typedef struct pico_uros_node_s {
  rcl_node_t node;
  rcl_allocator_t allocator;
  rclc_support_t support;
  rclc_executor_t executor;
} pico_uros_node_t;

extern pico_uros_node_t node;
extern rcl_publisher_t log_publisher;
extern rcl_publisher_t trace_publisher;

extern rcl_timer_t uptime_timer;
extern rcl_publisher_t uptime_publisher;

extern rcl_timer_t sensor_timer;

status_t create_node_pico(void);
void destroy_node_pico(void);