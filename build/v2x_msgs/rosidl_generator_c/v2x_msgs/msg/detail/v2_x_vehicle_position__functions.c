// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from v2x_msgs:msg/V2XVehiclePosition.idl
// generated code does not contain a copyright notice
#include "v2x_msgs/msg/detail/v2_x_vehicle_position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `vehicle_id`
#include "rosidl_runtime_c/string_functions.h"
// Member `position`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `covariance`
#include "geometry_msgs/msg/detail/vector3__functions.h"

bool
v2x_msgs__msg__V2XVehiclePosition__init(v2x_msgs__msg__V2XVehiclePosition * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    v2x_msgs__msg__V2XVehiclePosition__fini(msg);
    return false;
  }
  // vehicle_id
  if (!rosidl_runtime_c__String__init(&msg->vehicle_id)) {
    v2x_msgs__msg__V2XVehiclePosition__fini(msg);
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    v2x_msgs__msg__V2XVehiclePosition__fini(msg);
    return false;
  }
  // covariance
  if (!geometry_msgs__msg__Vector3__init(&msg->covariance)) {
    v2x_msgs__msg__V2XVehiclePosition__fini(msg);
    return false;
  }
  return true;
}

void
v2x_msgs__msg__V2XVehiclePosition__fini(v2x_msgs__msg__V2XVehiclePosition * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // vehicle_id
  rosidl_runtime_c__String__fini(&msg->vehicle_id);
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
  // covariance
  geometry_msgs__msg__Vector3__fini(&msg->covariance);
}

bool
v2x_msgs__msg__V2XVehiclePosition__are_equal(const v2x_msgs__msg__V2XVehiclePosition * lhs, const v2x_msgs__msg__V2XVehiclePosition * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // vehicle_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->vehicle_id), &(rhs->vehicle_id)))
  {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // covariance
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->covariance), &(rhs->covariance)))
  {
    return false;
  }
  return true;
}

bool
v2x_msgs__msg__V2XVehiclePosition__copy(
  const v2x_msgs__msg__V2XVehiclePosition * input,
  v2x_msgs__msg__V2XVehiclePosition * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // vehicle_id
  if (!rosidl_runtime_c__String__copy(
      &(input->vehicle_id), &(output->vehicle_id)))
  {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // covariance
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->covariance), &(output->covariance)))
  {
    return false;
  }
  return true;
}

v2x_msgs__msg__V2XVehiclePosition *
v2x_msgs__msg__V2XVehiclePosition__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  v2x_msgs__msg__V2XVehiclePosition * msg = (v2x_msgs__msg__V2XVehiclePosition *)allocator.allocate(sizeof(v2x_msgs__msg__V2XVehiclePosition), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(v2x_msgs__msg__V2XVehiclePosition));
  bool success = v2x_msgs__msg__V2XVehiclePosition__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
v2x_msgs__msg__V2XVehiclePosition__destroy(v2x_msgs__msg__V2XVehiclePosition * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    v2x_msgs__msg__V2XVehiclePosition__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
v2x_msgs__msg__V2XVehiclePosition__Sequence__init(v2x_msgs__msg__V2XVehiclePosition__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  v2x_msgs__msg__V2XVehiclePosition * data = NULL;

  if (size) {
    data = (v2x_msgs__msg__V2XVehiclePosition *)allocator.zero_allocate(size, sizeof(v2x_msgs__msg__V2XVehiclePosition), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = v2x_msgs__msg__V2XVehiclePosition__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        v2x_msgs__msg__V2XVehiclePosition__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
v2x_msgs__msg__V2XVehiclePosition__Sequence__fini(v2x_msgs__msg__V2XVehiclePosition__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      v2x_msgs__msg__V2XVehiclePosition__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

v2x_msgs__msg__V2XVehiclePosition__Sequence *
v2x_msgs__msg__V2XVehiclePosition__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  v2x_msgs__msg__V2XVehiclePosition__Sequence * array = (v2x_msgs__msg__V2XVehiclePosition__Sequence *)allocator.allocate(sizeof(v2x_msgs__msg__V2XVehiclePosition__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = v2x_msgs__msg__V2XVehiclePosition__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
v2x_msgs__msg__V2XVehiclePosition__Sequence__destroy(v2x_msgs__msg__V2XVehiclePosition__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    v2x_msgs__msg__V2XVehiclePosition__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
v2x_msgs__msg__V2XVehiclePosition__Sequence__are_equal(const v2x_msgs__msg__V2XVehiclePosition__Sequence * lhs, const v2x_msgs__msg__V2XVehiclePosition__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!v2x_msgs__msg__V2XVehiclePosition__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
v2x_msgs__msg__V2XVehiclePosition__Sequence__copy(
  const v2x_msgs__msg__V2XVehiclePosition__Sequence * input,
  v2x_msgs__msg__V2XVehiclePosition__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(v2x_msgs__msg__V2XVehiclePosition);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    v2x_msgs__msg__V2XVehiclePosition * data =
      (v2x_msgs__msg__V2XVehiclePosition *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!v2x_msgs__msg__V2XVehiclePosition__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          v2x_msgs__msg__V2XVehiclePosition__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!v2x_msgs__msg__V2XVehiclePosition__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
