#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to v2x_msgs__msg__V2XVehiclePosition

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct V2XVehiclePosition {
    /// 観測時刻 (stamp) と座標フレーム (frame_id, e.g. "map")
    pub header: std_msgs::msg::Header,

    /// 車両を識別する ID (e.g. "d1".."d4")
    pub vehicle_id: std::string::String,

    /// 各車両の位置 (header の frame_id 系)
    pub position: geometry_msgs::msg::Point,

    /// 位置不確実性 (x/y/z 軸の標準偏差)
    pub covariance: geometry_msgs::msg::Vector3,

}



impl Default for V2XVehiclePosition {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::V2XVehiclePosition::default())
  }
}

impl rosidl_runtime_rs::Message for V2XVehiclePosition {
  type RmwMsg = super::msg::rmw::V2XVehiclePosition;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        vehicle_id: msg.vehicle_id.as_str().into(),
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.position)).into_owned(),
        covariance: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Owned(msg.covariance)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        vehicle_id: msg.vehicle_id.as_str().into(),
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.position)).into_owned(),
        covariance: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Borrowed(&msg.covariance)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      vehicle_id: msg.vehicle_id.to_string(),
      position: geometry_msgs::msg::Point::from_rmw_message(msg.position),
      covariance: geometry_msgs::msg::Vector3::from_rmw_message(msg.covariance),
    }
  }
}


// Corresponds to v2x_msgs__msg__V2XVehiclePositionArray

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct V2XVehiclePositionArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub vehicles: Vec<super::msg::V2XVehiclePosition>,

}



impl Default for V2XVehiclePositionArray {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::V2XVehiclePositionArray::default())
  }
}

impl rosidl_runtime_rs::Message for V2XVehiclePositionArray {
  type RmwMsg = super::msg::rmw::V2XVehiclePositionArray;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        vehicles: msg.vehicles
          .into_iter()
          .map(|elem| super::msg::V2XVehiclePosition::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        vehicles: msg.vehicles
          .iter()
          .map(|elem| super::msg::V2XVehiclePosition::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      vehicles: msg.vehicles
          .into_iter()
          .map(super::msg::V2XVehiclePosition::from_rmw_message)
          .collect(),
    }
  }
}


