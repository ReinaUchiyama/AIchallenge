// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from v2x_msgs:msg/V2XVehiclePosition.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "v2x_msgs/msg/detail/v2_x_vehicle_position__rosidl_typesupport_introspection_c.h"
#include "v2x_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "v2x_msgs/msg/detail/v2_x_vehicle_position__functions.h"
#include "v2x_msgs/msg/detail/v2_x_vehicle_position__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `vehicle_id`
#include "rosidl_runtime_c/string_functions.h"
// Member `position`
#include "geometry_msgs/msg/point.h"
// Member `position`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"
// Member `covariance`
#include "geometry_msgs/msg/vector3.h"
// Member `covariance`
#include "geometry_msgs/msg/detail/vector3__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  v2x_msgs__msg__V2XVehiclePosition__init(message_memory);
}

void v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_fini_function(void * message_memory)
{
  v2x_msgs__msg__V2XVehiclePosition__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(v2x_msgs__msg__V2XVehiclePosition, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "vehicle_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(v2x_msgs__msg__V2XVehiclePosition, vehicle_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(v2x_msgs__msg__V2XVehiclePosition, position),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "covariance",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(v2x_msgs__msg__V2XVehiclePosition, covariance),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_message_members = {
  "v2x_msgs__msg",  // message namespace
  "V2XVehiclePosition",  // message name
  4,  // number of fields
  sizeof(v2x_msgs__msg__V2XVehiclePosition),
  v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_message_member_array,  // message members
  v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_init_function,  // function to initialize message memory (memory has to be allocated)
  v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_message_type_support_handle = {
  0,
  &v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_v2x_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, v2x_msgs, msg, V2XVehiclePosition)() {
  v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Vector3)();
  if (!v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_message_type_support_handle.typesupport_identifier) {
    v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &v2x_msgs__msg__V2XVehiclePosition__rosidl_typesupport_introspection_c__V2XVehiclePosition_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
