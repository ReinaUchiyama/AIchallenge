// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from v2x_msgs:msg/V2XVehiclePositionArray.idl
// generated code does not contain a copyright notice

#ifndef V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION_ARRAY__STRUCT_HPP_
#define V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'vehicles'
#include "v2x_msgs/msg/detail/v2_x_vehicle_position__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__v2x_msgs__msg__V2XVehiclePositionArray __attribute__((deprecated))
#else
# define DEPRECATED__v2x_msgs__msg__V2XVehiclePositionArray __declspec(deprecated)
#endif

namespace v2x_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct V2XVehiclePositionArray_
{
  using Type = V2XVehiclePositionArray_<ContainerAllocator>;

  explicit V2XVehiclePositionArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit V2XVehiclePositionArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _vehicles_type =
    std::vector<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator>>>;
  _vehicles_type vehicles;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__vehicles(
    const std::vector<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator>>> & _arg)
  {
    this->vehicles = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__v2x_msgs__msg__V2XVehiclePositionArray
    std::shared_ptr<v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__v2x_msgs__msg__V2XVehiclePositionArray
    std::shared_ptr<v2x_msgs::msg::V2XVehiclePositionArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const V2XVehiclePositionArray_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->vehicles != other.vehicles) {
      return false;
    }
    return true;
  }
  bool operator!=(const V2XVehiclePositionArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct V2XVehiclePositionArray_

// alias to use template instance with default allocator
using V2XVehiclePositionArray =
  v2x_msgs::msg::V2XVehiclePositionArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace v2x_msgs

#endif  // V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION_ARRAY__STRUCT_HPP_
