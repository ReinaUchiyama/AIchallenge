// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from v2x_msgs:msg/V2XVehiclePosition.idl
// generated code does not contain a copyright notice

#ifndef V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION__STRUCT_H_
#define V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'vehicle_id'
#include "rosidl_runtime_c/string.h"
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'covariance'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/V2XVehiclePosition in the package v2x_msgs.
typedef struct v2x_msgs__msg__V2XVehiclePosition
{
  /// 観測時刻 (stamp) と座標フレーム (frame_id, e.g. "map")
  std_msgs__msg__Header header;
  /// 車両を識別する ID (e.g. "d1".."d4")
  rosidl_runtime_c__String vehicle_id;
  /// 各車両の位置 (header の frame_id 系)
  geometry_msgs__msg__Point position;
  /// 位置不確実性 (x/y/z 軸の標準偏差)
  geometry_msgs__msg__Vector3 covariance;
} v2x_msgs__msg__V2XVehiclePosition;

// Struct for a sequence of v2x_msgs__msg__V2XVehiclePosition.
typedef struct v2x_msgs__msg__V2XVehiclePosition__Sequence
{
  v2x_msgs__msg__V2XVehiclePosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} v2x_msgs__msg__V2XVehiclePosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION__STRUCT_H_
