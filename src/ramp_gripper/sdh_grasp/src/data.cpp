#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <fstream>
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

ros::ServiceClient client;

std::ofstream myfile;
std::ofstream myfile1;



void tactileCallback(const schunk_sdh::TactileSensor::ConstPtr& msg)
 {     
     int sum = 0;

     ros::Time begin = ros::Time::now();

     int sz = msg->tactile_matrix[sensorID].cells_x * msg->tactile_matrix[sensorID].cells_y ;

     myfile1 << "Sensor id  = "<<sensorID;
     myfile1 <<",";
     myfile1 <<"Time = " << begin;
     myfile1<< "\n";
     for (int i = 0; i < sz; i++)
     {
         int val = msg->tactile_matrix[sensorID].tactile_array[i];
         sum = sum +val;

         myfile1 << val;
         myfile1 <<",";

         if( (i+1)%6 == 0 )
         {
             myfile1<< "\n";
         }
     }

     myfile <<"Time = " << begin;
     myfile <<",";
     myfile << sum;
     myfile <<",";
     myfile <<",";

      sum = 0;

     sensorID = sensorID + 1 ;
     if(sensorID > 5)
     {
        sensorID = 0 ;
        myfile << "\n";
     }
 }



int main(int argc, char **argv)
{
    sensorID = 0;

    myfile.open ("data_log_sum.csv");
    myfile1.open ("data_log raw.csv");

    ros::init(argc, argv, "tactile_data_logger");

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

    ros::Subscriber sub2 = n.subscribe("/dsa_controller/tactile_data", 1000, tactileCallback);

    ros::spin();

    myfile.close();
    myfile.close();

    return 0;
}




