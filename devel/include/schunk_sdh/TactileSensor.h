// Generated by gencpp from file schunk_sdh/TactileSensor.msg
// DO NOT EDIT!


#ifndef SCHUNK_SDH_MESSAGE_TACTILESENSOR_H
#define SCHUNK_SDH_MESSAGE_TACTILESENSOR_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <schunk_sdh/TactileMatrix.h>

namespace schunk_sdh
{
template <class ContainerAllocator>
struct TactileSensor_
{
  typedef TactileSensor_<ContainerAllocator> Type;

  TactileSensor_()
    : header()
    , tactile_matrix()  {
    }
  TactileSensor_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , tactile_matrix(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector< ::schunk_sdh::TactileMatrix_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::schunk_sdh::TactileMatrix_<ContainerAllocator> >::other >  _tactile_matrix_type;
  _tactile_matrix_type tactile_matrix;




  typedef boost::shared_ptr< ::schunk_sdh::TactileSensor_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::schunk_sdh::TactileSensor_<ContainerAllocator> const> ConstPtr;

}; // struct TactileSensor_

typedef ::schunk_sdh::TactileSensor_<std::allocator<void> > TactileSensor;

typedef boost::shared_ptr< ::schunk_sdh::TactileSensor > TactileSensorPtr;
typedef boost::shared_ptr< ::schunk_sdh::TactileSensor const> TactileSensorConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::schunk_sdh::TactileSensor_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::schunk_sdh::TactileSensor_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace schunk_sdh

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'schunk_sdh': ['/home/mjmj/catkin_ws_mike/src/ramp_gripper/schunk_sdh/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::schunk_sdh::TactileSensor_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::schunk_sdh::TactileSensor_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::schunk_sdh::TactileSensor_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::schunk_sdh::TactileSensor_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::schunk_sdh::TactileSensor_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::schunk_sdh::TactileSensor_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::schunk_sdh::TactileSensor_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c6176a03c00cccf1b8efd3037de0d45d";
  }

  static const char* value(const ::schunk_sdh::TactileSensor_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc6176a03c00cccf1ULL;
  static const uint64_t static_value2 = 0xb8efd3037de0d45dULL;
};

template<class ContainerAllocator>
struct DataType< ::schunk_sdh::TactileSensor_<ContainerAllocator> >
{
  static const char* value()
  {
    return "schunk_sdh/TactileSensor";
  }

  static const char* value(const ::schunk_sdh::TactileSensor_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::schunk_sdh::TactileSensor_<ContainerAllocator> >
{
  static const char* value()
  {
    return "#tactile sensor data in 2D grid\n\
Header header\n\
schunk_sdh/TactileMatrix[] tactile_matrix\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: schunk_sdh/TactileMatrix\n\
uint32 matrix_id\n\
int16 cells_x\n\
int16 cells_y\n\
int16[] tactile_array\n\
";
  }

  static const char* value(const ::schunk_sdh::TactileSensor_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::schunk_sdh::TactileSensor_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.tactile_matrix);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct TactileSensor_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::schunk_sdh::TactileSensor_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::schunk_sdh::TactileSensor_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "tactile_matrix[]" << std::endl;
    for (size_t i = 0; i < v.tactile_matrix.size(); ++i)
    {
      s << indent << "  tactile_matrix[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::schunk_sdh::TactileMatrix_<ContainerAllocator> >::stream(s, indent + "    ", v.tactile_matrix[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // SCHUNK_SDH_MESSAGE_TACTILESENSOR_H
