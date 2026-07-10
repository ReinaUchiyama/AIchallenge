// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from v2x_msgs:msg/V2XVehiclePosition.idl
// generated code does not contain a copyright notice

#ifndef V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION__BUILDER_HPP_
#define V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "v2x_msgs/msg/detail/v2_x_vehicle_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace v2x_msgs
{

namespace msg
{

namespace builder
{

class Init_V2XVehiclePosition_covariance
{
public:
  explicit Init_V2XVehiclePosition_covariance(::v2x_msgs::msg::V2XVehiclePosition & msg)
  : msg_(msg)
  {}
  ::v2x_msgs::msg::V2XVehiclePosition covariance(::v2x_msgs::msg::V2XVehiclePosition::_covariance_type arg)
  {
    msg_.covariance = std::move(arg);
    return std::move(msg_);
  }

private:
  ::v2x_msgs::msg::V2XVehiclePosition msg_;
};

class Init_V2XVehiclePosition_position
{
public:
  explicit Init_V2XVehiclePosition_position(::v2x_msgs::msg::V2XVehiclePosition & msg)
  : msg_(msg)
  {}
  Init_V2XVehiclePosition_covariance position(::v2x_msgs::msg::V2XVehiclePosition::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_V2XVehiclePosition_covariance(msg_);
  }

private:
  ::v2x_msgs::msg::V2XVehiclePosition msg_;
};

class Init_V2XVehiclePosition_vehicle_id
{
public:
  explicit Init_V2XVehiclePosition_vehicle_id(::v2x_msgs::msg::V2XVehiclePosition & msg)
  : msg_(msg)
  {}
  Init_V2XVehiclePosition_position vehicle_id(::v2x_msgs::msg::V2XVehiclePosition::_vehicle_id_type arg)
  {
    msg_.vehicle_id = std::move(arg);
    return Init_V2XVehiclePosition_position(msg_);
  }

private:
  ::v2x_msgs::msg::V2XVehiclePosition msg_;
};

class Init_V2XVehiclePosition_header
{
public:
  Init_V2XVehiclePosition_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_V2XVehiclePosition_vehicle_id header(::v2x_msgs::msg::V2XVehiclePosition::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_V2XVehiclePosition_vehicle_id(msg_);
  }

private:
  ::v2x_msgs::msg::V2XVehiclePosition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::v2x_msgs::msg::V2XVehiclePosition>()
{
  return v2x_msgs::msg::builder::Init_V2XVehiclePosition_header();
}

}  // namespace v2x_msgs

#endif  // V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION__BUILDER_HPP_
