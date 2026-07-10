// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from v2x_msgs:msg/V2XVehiclePosition.idl
// generated code does not contain a copyright notice

#ifndef V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION__STRUCT_HPP_
#define V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION__STRUCT_HPP_

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
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'covariance'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__v2x_msgs__msg__V2XVehiclePosition __attribute__((deprecated))
#else
# define DEPRECATED__v2x_msgs__msg__V2XVehiclePosition __declspec(deprecated)
#endif

namespace v2x_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct V2XVehiclePosition_
{
  using Type = V2XVehiclePosition_<ContainerAllocator>;

  explicit V2XVehiclePosition_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    position(_init),
    covariance(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->vehicle_id = "";
    }
  }

  explicit V2XVehiclePosition_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    vehicle_id(_alloc),
    position(_alloc, _init),
    covariance(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->vehicle_id = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _vehicle_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _vehicle_id_type vehicle_id;
  using _position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _position_type position;
  using _covariance_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _covariance_type covariance;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__vehicle_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->vehicle_id = _arg;
    return *this;
  }
  Type & set__position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__covariance(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->covariance = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator> *;
  using ConstRawPtr =
    const v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__v2x_msgs__msg__V2XVehiclePosition
    std::shared_ptr<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__v2x_msgs__msg__V2XVehiclePosition
    std::shared_ptr<v2x_msgs::msg::V2XVehiclePosition_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const V2XVehiclePosition_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->vehicle_id != other.vehicle_id) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->covariance != other.covariance) {
      return false;
    }
    return true;
  }
  bool operator!=(const V2XVehiclePosition_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct V2XVehiclePosition_

// alias to use template instance with default allocator
using V2XVehiclePosition =
  v2x_msgs::msg::V2XVehiclePosition_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace v2x_msgs

#endif  // V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION__STRUCT_HPP_
