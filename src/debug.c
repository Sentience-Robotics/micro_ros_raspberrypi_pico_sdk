#include "debug.h"

#include <std_msgs/msg/string.h>

#include "constant.h"
#include "ros.h"

void empile_trace(const char *function_name) {
  char output[MAX_LOG_SIZE];
  std_msgs__msg__String msg;

  sprintf(output, "Empile %s", function_name);
  msg.data.data = output;
  msg.data.size = strlen(output);
  msg.data.capacity = msg.data.size + 1;
  rcl_publish(&trace_publisher, &msg, NULL);
}

void depile_trace(const char *function_name) {
  char output[MAX_LOG_SIZE];
  std_msgs__msg__String msg;

  sprintf(output, "Depile %s", function_name);
  msg.data.data = output;
  msg.data.size = strlen(output);
  msg.data.capacity = msg.data.size + 1;
  rcl_publish(&trace_publisher, &msg, NULL);
}

void send_log(const char *format, ...) {
  va_list list;
  char output[MAX_LOG_SIZE];
  std_msgs__msg__String msg;

  va_start(list, format);
  vsnprintf(output, MAX_LOG_SIZE, format, list);
  msg.data.data = output;
  msg.data.size = strlen(output);
  msg.data.capacity = msg.data.size + 1;
  rcl_publish(&log_publisher, &msg, NULL);
  va_end(list);
}
