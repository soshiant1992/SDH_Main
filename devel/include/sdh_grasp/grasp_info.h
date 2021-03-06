// Generated by gencpp from file sdh_grasp/grasp_info.msg
// DO NOT EDIT!


#ifndef SDH_GRASP_MESSAGE_GRASP_INFO_H
#define SDH_GRASP_MESSAGE_GRASP_INFO_H


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
struct grasp_info_
{
  typedef grasp_info_<ContainerAllocator> Type;

  grasp_info_()
    : state(false)
    , type()  {
    }
  grasp_info_(const ContainerAllocator& _alloc)
    : state(false)
    , type(_alloc)  {
  (void)_alloc;
    }



   typedef uint8_t _state_type;
  _state_type state;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _type_type;
  _type_type type;




  typedef boost::shared_ptr< ::sdh_grasp::grasp_info_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::sdh_grasp::grasp_info_<ContainerAllocator> const> ConstPtr;

}; // struct grasp_info_

typedef ::sdh_grasp::grasp_info_<std::allocator<void> > grasp_info;

typedef boost::shared_ptr< ::sdh_grasp::grasp_info > grasp_infoPtr;
typedef boost::shared_ptr< ::sdh_grasp::grasp_info const> grasp_infoConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::sdh_grasp::grasp_info_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::sdh_grasp::grasp_info_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::sdh_grasp::grasp_info_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::sdh_grasp::grasp_info_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::sdh_grasp::grasp_info_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::sdh_grasp::grasp_info_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sdh_grasp::grasp_info_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sdh_grasp::grasp_info_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::sdh_grasp::grasp_info_<ContainerAllocator> >
{
  static const char* value()
  {
    return "cf9efc9a129a5751020d43b2fc5efbd0";
  }

  static const char* value(const ::sdh_grasp::grasp_info_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xcf9efc9a129a5751ULL;
  static const uint64_t static_value2 = 0x020d43b2fc5efbd0ULL;
};

template<class ContainerAllocator>
struct DataType< ::sdh_grasp::grasp_info_<ContainerAllocator> >
{
  static const char* value()
  {
    return "sdh_grasp/grasp_info";
  }

  static const char* value(const ::sdh_grasp::grasp_info_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::sdh_grasp::grasp_info_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool state\n\
string type\n\
";
  }

  static const char* value(const ::sdh_grasp::grasp_info_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::sdh_grasp::grasp_info_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.state);
      stream.next(m.type);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct grasp_info_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::sdh_grasp::grasp_info_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::sdh_grasp::grasp_info_<ContainerAllocator>& v)
  {
    s << indent << "state: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.state);
    s << indent << "type: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.type);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SDH_GRASP_MESSAGE_GRASP_INFO_H
