// Generated by gencpp from file sdh_grasp/pre_grasp_pos_data.msg
// DO NOT EDIT!


#ifndef SDH_GRASP_MESSAGE_PRE_GRASP_POS_DATA_H
#define SDH_GRASP_MESSAGE_PRE_GRASP_POS_DATA_H


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
struct pre_grasp_pos_data_
{
  typedef pre_grasp_pos_data_<ContainerAllocator> Type;

  pre_grasp_pos_data_()
    : data()
    , type()  {
    }
  pre_grasp_pos_data_(const ContainerAllocator& _alloc)
    : data(_alloc)
    , type(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _data_type;
  _data_type data;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _type_type;
  _type_type type;




  typedef boost::shared_ptr< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> const> ConstPtr;

}; // struct pre_grasp_pos_data_

typedef ::sdh_grasp::pre_grasp_pos_data_<std::allocator<void> > pre_grasp_pos_data;

typedef boost::shared_ptr< ::sdh_grasp::pre_grasp_pos_data > pre_grasp_pos_dataPtr;
typedef boost::shared_ptr< ::sdh_grasp::pre_grasp_pos_data const> pre_grasp_pos_dataConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4d52d6e0d781ec5908fc845dc781b11d";
  }

  static const char* value(const ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4d52d6e0d781ec59ULL;
  static const uint64_t static_value2 = 0x08fc845dc781b11dULL;
};

template<class ContainerAllocator>
struct DataType< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "sdh_grasp/pre_grasp_pos_data";
  }

  static const char* value(const ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64[] data\n\
string type\n\
";
  }

  static const char* value(const ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.data);
      stream.next(m.type);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct pre_grasp_pos_data_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::sdh_grasp::pre_grasp_pos_data_<ContainerAllocator>& v)
  {
    s << indent << "data[]" << std::endl;
    for (size_t i = 0; i < v.data.size(); ++i)
    {
      s << indent << "  data[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.data[i]);
    }
    s << indent << "type: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.type);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SDH_GRASP_MESSAGE_PRE_GRASP_POS_DATA_H