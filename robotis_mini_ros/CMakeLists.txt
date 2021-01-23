cmake_minimum_required(VERSION 3.0.2)
project(robotis_mini_ros)

#cmake_policy(VERSION <min>[...<max>])
cmake_policy(SET CMP0057 NEW)

set(CMAKE_CXX_STANDARD 14)

find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)

################################################
## Declare ROS messages, services and actions ##
################################################

set(msg_files
  msg/Imu.msg
  msg/Xl320Info.msg
  msg/Xl320State.msg
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES builtin_interfaces
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()
