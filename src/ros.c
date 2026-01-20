#include "ros.h"

#include <rclc/publisher.h>
#include <rclc/rclc.h>
#include <rclc/types.h>
#include <rmw_microros/rmw_microros.h>
#include <rosidl_runtime_c/message_type_support_struct.h>
#include <rosidl_typesupport_interface/macros.h>

#include <sensor_msgs/msg/joint_state.h>
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/string.h>
#include <lucy_msgs/msg/raw_sensor.h>

#include "board.h"
#include "constant.h"
#include "debug.h"
#include "enum.h"
#include "joint.h"
#include "ws2812_set_rgb.h"
#include "pico_uart_transports/pico_uart_transports.h"

pico_uros_node_t node;
rcl_publisher_t log_publisher;
rcl_publisher_t trace_publisher;

rcl_timer_t uptime_timer;
rcl_publisher_t uptime_publisher;


rcl_timer_t sensor_timer;

/**
 * Callback function for the uptime timer
 */
static void uptime_timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
  empile_trace("uptime_timer_callback");

  static std_msgs__msg__Int32 uptime = {};
  static bool ledOn = false;

  rcl_publish(&uptime_publisher, &uptime, NULL);
  ws2812_set_rgb(5, 0, ledOn * 10, 0);
  uptime.data = (uptime.data + 1);
  ledOn = !ledOn;

  depile_trace("uptime_timer_callback");
}

static void sensor_timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
  empile_trace("sensor_timer_callback");

  for (uint32_t i = 0; i < NB_BOARDS; i++) {
    if (boards[i].on_sensor_timer_tick != NULL) {
      boards[i].on_sensor_timer_tick(&boards[i]);
    }
  }
  rcl_ret_t status = rcl_publish(&sensor_publisher, &sensor_publisher_data, NULL);

  depile_trace("sensor_timer_callback");
}

/**
 * Callback function for the joint subscriber
 */
static void joint_subscriber_callback(const sensor_msgs__msg__JointState *inputs)
{
  empile_trace("joint_subscriber_callback");

  for (size_t i = 0; i < NB_BOARDS; i++) {
    if (boards[i].on_joint_subscriber_update != NULL) {
      boards[i].on_joint_subscriber_update(&boards[i], inputs);
    }
  }

  depile_trace("joint_subscriber_callback");
}


/**
 * Ping the ROS2 agent to check the connection
 * @param timeout_ms: timeout in milliseconds
 * @param nb_attempts: number of attempts
 * @return: OK if the agent is reachable, KO otherwise
 */
status_t ping_agent(int timeout_ms, int nb_attempts) {
  rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, nb_attempts);
  if (ret != RCL_RET_OK) {
    return KO;
  }
  return OK;
}

/**
 * Create the ROS2 node and its components
 * @return OK if the node is created successfully, KO otherwise
 */
status_t create_node_pico(void) {
  node.allocator = rcl_get_default_allocator();
  if (rclc_support_init(&node.support, 0, NULL, &node.allocator) != RCL_RET_OK) {
    return KO;
  }
  if (rclc_node_init_default(&node.node, NODE_NAME, "", &node.support) != RCL_RET_OK) {
    return KO;
  }
  if (rclc_executor_init(&node.executor, &node.support.context, NB_HANDLES, &node.allocator) != RCL_RET_OK) {
    return KO;
  }
  // UPTIME
  rclc_timer_init_default(&uptime_timer, &node.support, UPTIME_TIMER_INTERVAL, &uptime_timer_callback);
  rclc_executor_add_timer(&node.executor, &uptime_timer);
  rclc_publisher_init_default(&uptime_publisher, &node.node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32), UPTIME_PUBLISHER_TOPIC_NAME);

  // SENSORS
  rclc_timer_init_default(&sensor_timer, &node.support, SENSOR_TIMER_INTERVAL, &sensor_timer_callback);
  rclc_executor_add_timer(&node.executor, &sensor_timer);
  rclc_publisher_init_default(&sensor_publisher, &node.node, ROSIDL_GET_MSG_TYPE_SUPPORT(lucy_msgs, msg, RawSensor), SENSORS_TOPIC_NAME);

  // JOINTS
  rclc_subscription_init_default(&joint_subscriber, &node.node, ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, JointState), JOINTS_TOPIC_NAME);
  rclc_executor_add_subscription(&node.executor, &joint_subscriber, &joint_subscriber_data, (void (*)(const void *))&joint_subscriber_callback, ON_NEW_DATA);

  // DEBUG
  rclc_publisher_init_default(&log_publisher, &node.node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String), LOG_PUBLISHER_TOPIC_NAME);
  rclc_publisher_init_default(&trace_publisher, &node.node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String), TRACE_PUBLISHER_TOPIC_NAME);

  return OK;
}

/**
 * Destroy the ROS2 node and its components
 */
void destroy_node_pico(void) {
  rcl_publisher_fini(&trace_publisher, &node.node);
  rcl_publisher_fini(&log_publisher, &node.node);

  rclc_executor_remove_subscription(&node.executor, &joint_subscriber);
  rcl_subscription_fini(&joint_subscriber, &node.node);

  rclc_executor_remove_timer(&node.executor, &sensor_timer);
  rcl_timer_fini(&sensor_timer);
  rcl_publisher_fini(&sensor_publisher, &node.node);

  rclc_executor_remove_timer(&node.executor, &uptime_timer);
  rcl_timer_fini(&uptime_timer);
  rcl_publisher_fini(&uptime_publisher, &node.node);

  rcl_node_fini(&node.node);
  rclc_executor_fini(&node.executor);
  rcl_shutdown(&node.support.context);
  rclc_support_fini(&node.support);
}