// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from v2x_msgs:msg/V2XVehiclePositionArray.idl
// generated code does not contain a copyright notice

#ifndef V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION_ARRAY__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION_ARRAY__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "v2x_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "v2x_msgs/msg/detail/v2_x_vehicle_position_array__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace v2x_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_msgs
cdr_serialize(
  const v2x_msgs::msg::V2XVehiclePositionArray & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  v2x_msgs::msg::V2XVehiclePositionArray & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_msgs
get_serialized_size(
  const v2x_msgs::msg::V2XVehiclePositionArray & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_msgs
max_serialized_size_V2XVehiclePositionArray(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace v2x_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_v2x_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, v2x_msgs, msg, V2XVehiclePositionArray)();

#ifdef __cplusplus
}
#endif

#endif  // V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION_ARRAY__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
