#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "v2x_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__v2x_msgs__msg__V2XVehiclePosition() -> *const std::ffi::c_void;
}

#[link(name = "v2x_msgs__rosidl_generator_c")]
extern "C" {
    fn v2x_msgs__msg__V2XVehiclePosition__init(msg: *mut V2XVehiclePosition) -> bool;
    fn v2x_msgs__msg__V2XVehiclePosition__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<V2XVehiclePosition>, size: usize) -> bool;
    fn v2x_msgs__msg__V2XVehiclePosition__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<V2XVehiclePosition>);
    fn v2x_msgs__msg__V2XVehiclePosition__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<V2XVehiclePosition>, out_seq: *mut rosidl_runtime_rs::Sequence<V2XVehiclePosition>) -> bool;
}

// Corresponds to v2x_msgs__msg__V2XVehiclePosition
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct V2XVehiclePosition {
    /// 観測時刻 (stamp) と座標フレーム (frame_id, e.g. "map")
    pub header: std_msgs::msg::rmw::Header,

    /// 車両を識別する ID (e.g. "d1".."d4")
    pub vehicle_id: rosidl_runtime_rs::String,

    /// 各車両の位置 (header の frame_id 系)
    pub position: geometry_msgs::msg::rmw::Point,

    /// 位置不確実性 (x/y/z 軸の標準偏差)
    pub covariance: geometry_msgs::msg::rmw::Vector3,

}



impl Default for V2XVehiclePosition {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !v2x_msgs__msg__V2XVehiclePosition__init(&mut msg as *mut _) {
        panic!("Call to v2x_msgs__msg__V2XVehiclePosition__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for V2XVehiclePosition {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_msgs__msg__V2XVehiclePosition__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_msgs__msg__V2XVehiclePosition__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_msgs__msg__V2XVehiclePosition__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for V2XVehiclePosition {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for V2XVehiclePosition where Self: Sized {
  const TYPE_NAME: &'static str = "v2x_msgs/msg/V2XVehiclePosition";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__v2x_msgs__msg__V2XVehiclePosition() }
  }
}


#[link(name = "v2x_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__v2x_msgs__msg__V2XVehiclePositionArray() -> *const std::ffi::c_void;
}

#[link(name = "v2x_msgs__rosidl_generator_c")]
extern "C" {
    fn v2x_msgs__msg__V2XVehiclePositionArray__init(msg: *mut V2XVehiclePositionArray) -> bool;
    fn v2x_msgs__msg__V2XVehiclePositionArray__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<V2XVehiclePositionArray>, size: usize) -> bool;
    fn v2x_msgs__msg__V2XVehiclePositionArray__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<V2XVehiclePositionArray>);
    fn v2x_msgs__msg__V2XVehiclePositionArray__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<V2XVehiclePositionArray>, out_seq: *mut rosidl_runtime_rs::Sequence<V2XVehiclePositionArray>) -> bool;
}

// Corresponds to v2x_msgs__msg__V2XVehiclePositionArray
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct V2XVehiclePositionArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub vehicles: rosidl_runtime_rs::Sequence<super::super::msg::rmw::V2XVehiclePosition>,

}



impl Default for V2XVehiclePositionArray {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !v2x_msgs__msg__V2XVehiclePositionArray__init(&mut msg as *mut _) {
        panic!("Call to v2x_msgs__msg__V2XVehiclePositionArray__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for V2XVehiclePositionArray {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_msgs__msg__V2XVehiclePositionArray__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_msgs__msg__V2XVehiclePositionArray__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { v2x_msgs__msg__V2XVehiclePositionArray__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for V2XVehiclePositionArray {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for V2XVehiclePositionArray where Self: Sized {
  const TYPE_NAME: &'static str = "v2x_msgs/msg/V2XVehiclePositionArray";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__v2x_msgs__msg__V2XVehiclePositionArray() }
  }
}


