#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Bool.h>

#include "string.h"
#include "sensor_msgs/JointState.h"

#include <schunk_sdh/TactileSensor.h>
#include <schunk_sdh/TactileMatrix.h>
#include "std_srvs/Trigger.h"


int sensorID;
int tactile_flag;
int position_flag;



std_msgs::Int32MultiArray array_tactile;
std_msgs::Float32MultiArray array_pos;


ros::Publisher pub_tactile;
ros::Publisher pub_pos;

ros::ServiceClient client;

void update_control_flag(const std_msgs::Bool::ConstPtr& msg)
{
    tactile_flag =1;

}



void tactileCallback(const schunk_sdh::TactileSensor::ConstPtr& msg)
 {

   if( tactile_flag == 1)
   {

     std::string data("");
     int max  = 0 ;
     int sz = msg->tactile_matrix[sensorID].cells_x * msg->tactile_matrix[sensorID].cells_y ;
     for (int i = 0; i < sz; i++)
     {
         int val = msg->tactile_matrix[sensorID].tactile_array[i];
         if(max < val)
         {
            max  = val ;
         }
        std::ostringstream ss;
        ss << val;
        data.append(ss.str());
        data.append(", ");

        ss.flush();
     }
     

        array_tactile.data.push_back(max);
        ROS_INFO("Tactile sensor: [%d]  max_value: [%d]", sensorID, max);

     sensorID = sensorID + 1 ;
     if(sensorID > 5)
     {
        sensorID = 0 ;
        pub_tactile.publish(array_tactile);
        array_tactile.data.clear();
        tactile_flag = 0;
     }


   }


 }



void update_get_pos (const std_msgs::Bool::ConstPtr& msg)
{
    position_flag =1;

}



void jointCallback(const sensor_msgs::JointState::ConstPtr& msg)
{
    if(position_flag == 1)
    {
        std::stringstream ss;

        for(size_t i = 0; i < msg->position.size(); ++i)
            {
                if(i != 0)
                ss << ",";
                ss << msg->position[i];
                //ROS_INFO("pos = %f" ,  msg->position[i] );
                array_pos.data.push_back(msg->position[i]);
             }
        std::string s = ss.str();

        pub_pos.publish(array_pos);
        array_pos.data.clear();

        ROS_INFO("Position: [%s]", s.c_str());
        position_flag = 0;
    }

 }


int main(int argc, char **argv)
{
	sensorID = 0;
    tactile_flag  = 0;
    position_flag = 0;
    ros::init(argc, argv, "sdh_read");

    array_tactile.data.clear();
    array_pos.data.clear();

    ros::NodeHandle n;


    ros::ServiceClient client = n.serviceClient<std_srvs::Trigger>("/driver/init");
    std_srvs::Trigger srv ;

    if (client.call(srv))
    {
    }
      else
    {
     ROS_ERROR("Failed to call service driver/init");
     return 1;
    }



    pub_tactile = n.advertise<std_msgs::Int32MultiArray>("sdh_read/tactile_data" , 1000) ;
    pub_pos = n.advertise <std_msgs::Float32MultiArray>("sdh_read/pos_data" , 1000) ;

    ros::Subscriber sub1 = n.subscribe("sdh_read/get_tactile", 1000, update_control_flag);
    ros::Subscriber sub2 = n.subscribe("/dsa_controller/tactile_data", 1000, tactileCallback);
    ros::Subscriber sub3 = n.subscribe("sdh_read/get_pos", 1000, update_get_pos);
    ros::Subscriber sub4 = n.subscribe("/joint_states", 1000, jointCallback);

    ros::spin();

    return 0;
}




