cmake_minimum_required(VERSION 3.8)
project(lucy_msgs)

# find dependencies
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/RawSensor.msg"
)
ament_package()