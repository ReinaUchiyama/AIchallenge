// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from v2x_msgs:msg/V2XVehiclePositionArray.idl
// generated code does not contain a copyright notice

#ifndef V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION_ARRAY__BUILDER_HPP_
#define V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "v2x_msgs/msg/detail/v2_x_vehicle_position_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace v2x_msgs
{

namespace msg
{

namespace builder
{

class Init_V2XVehiclePositionArray_vehicles
{
public:
  explicit Init_V2XVehiclePositionArray_vehicles(::v2x_msgs::msg::V2XVehiclePositionArray & msg)
  : msg_(msg)
  {}
  ::v2x_msgs::msg::V2XVehiclePositionArray vehicles(::v2x_msgs::msg::V2XVehiclePositionArray::_vehicles_type arg)
  {
    msg_.vehicles = std::move(arg);
    return std::move(msg_);
  }

private:
  ::v2x_msgs::msg::V2XVehiclePositionArray msg_;
};

class Init_V2XVehiclePositionArray_header
{
public:
  Init_V2XVehiclePositionArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_V2XVehiclePositionArray_vehicles header(::v2x_msgs::msg::V2XVehiclePositionArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_V2XVehiclePositionArray_vehicles(msg_);
  }

private:
  ::v2x_msgs::msg::V2XVehiclePositionArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::v2x_msgs::msg::V2XVehiclePositionArray>()
{
  return v2x_msgs::msg::builder::Init_V2XVehiclePositionArray_header();
}

}  // namespace v2x_msgs

#endif  // V2X_MSGS__MSG__DETAIL__V2_X_VEHICLE_POSITION_ARRAY__BUILDER_HPP_
