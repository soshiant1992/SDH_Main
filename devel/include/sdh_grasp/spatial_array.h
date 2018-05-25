// Generated by gencpp from file sdh_grasp/spatial_array.msg
// DO NOT EDIT!


#ifndef SDH_GRASP_MESSAGE_SPATIAL_ARRAY_H
#define SDH_GRASP_MESSAGE_SPATIAL_ARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace sdh_grasp
{
template <class ContainerAllocator>
struct spatial_array_
{
  typedef spatial_array_<ContainerAllocator> Type;

  spatial_array_()
    : type()
    , x(0.0)
    , y(0.0)
    , z(0.0)  {
    }
  spatial_array_(const ContainerAllocator& _alloc)
    : type(_alloc)
    , x(0.0)
    , y(0.0)
    , z(0.0)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _type_type;
  _type_type type;

   typedef double _x_type;
  _x_type x;

   typedef double _y_type;
  _y_type y;

   typedef double _z_type;
  _z_type z;




  typedef boost::shared_ptr< ::sdh_grasp::spatial_array_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::sdh_grasp::spatial_array_<ContainerAllocator> const> ConstPtr;

}; // struct spatial_array_

typedef ::sdh_grasp::spatial_array_<std::allocator<void> > spatial_array;

typedef boost::shared_ptr< ::sdh_grasp::spatial_array > spatial_arrayPtr;
typedef boost::shared_ptr< ::sdh_grasp::spatial_array const> spatial_arrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::sdh_grasp::spatial_array_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::sdh_grasp::spatial_array_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace sdh_grasp

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'sdh_grasp': ['/home/mjmj/catkin_ws_mike/src/ramp_gripper/sdh_grasp/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::sdh_grasp::spatial_array_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::sdh_grasp::spatial_array_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::sdh_grasp::spatial_array_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::sdh_grasp::spatial_array_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sdh_grasp::spatial_array_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sdh_grasp::spatial_array_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::sdh_grasp::spatial_array_<ContainerAllocator> >
{
  static const char* value()
  {
    return "56cb4f6a21fb914cb4077b5d2eafdd6d";
  }

  static const char* value(const ::sdh_grasp::spatial_array_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x56cb4f6a21fb914cULL;
  static const uint64_t static_value2 = 0xb4077b5d2eafdd6dULL;
};

template<class ContainerAllocator>
struct DataType< ::sdh_grasp::spatial_array_<ContainerAllocator> >
{
  static const char* value()
  {
    return "sdh_grasp/spatial_array";
  }

  static const char* value(const ::sdh_grasp::spatial_array_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::sdh_grasp::spatial_array_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string type\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const ::sdh_grasp::spatial_array_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::sdh_grasp::spatial_array_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.type);
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.z);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct spatial_array_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::sdh_grasp::spatial_array_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::sdh_grasp::spatial_array_<ContainerAllocator>& v)
  {
    s << indent << "type: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.type);
    s << indent << "x: ";
    Printer<double>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<double>::stream(s, indent + "  ", v.y);
    s << indent << "z: ";
    Printer<double>::stream(s, indent + "  ", v.z);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SDH_GRASP_MESSAGE_SPATIAL_ARRAY_H
