#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include <sdh_grasp/pre_grasp_pos_data.h>
#include"std_msgs/String.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
using namespace std;
int main(int argc, char **argv)
{


    ros::init(argc, argv, "threshold");

    ros::NodeHandle n;
            sdh_grasp::pre_grasp_pos_data xyz;

            xyz.type = "sphere";
            xyz.data.push_back((0*M_PI)/180);
            xyz.data.push_back((-50*M_PI)/180);
            xyz.data.push_back((10*M_PI)/180);
            xyz.data.push_back((-50*M_PI)/180);
            xyz.data.push_back((10*M_PI)/180);
            xyz.data.push_back((-50*M_PI)/180);
            xyz.data.push_back((10*M_PI)/180);


//            xyz.type = "lateral";
//            xyz.data.push_back((0*M_PI)/180);
//            xyz.data.push_back((-0*M_PI)/180);
//            xyz.data.push_back((-0*M_PI)/180);
//            xyz.data.push_back((-0*M_PI)/180);
//            xyz.data.push_back((-0*M_PI)/180);
//            xyz.data.push_back((-0*M_PI)/180);
//            xyz.data.push_back((-0*M_PI)/180);

            ros::Publisher  pub3 = n. advertise<sdh_grasp::pre_grasp_pos_data>("/sdh_grasp_control/pre_grasp_config", 1,true);
//            ros::Publisher  pub3 = n. advertise<sdh_grasp::pre_grasp_pos_data>("/backoff", 1,true);
            ros::Publisher  pub4 = n. advertise<std_msgs::String>("/hand_fine_backoff", 1,true);

//while(ros::ok){
            for (int var = 0; var < 2; ++var) {

std_msgs::String namino ;
namino.data="cube";
//                   pub3.publish(xyz);
                   pub4.publish(namino);
                   ros::Rate loop_rate(5);
                   loop_rate.sleep();
                   cout<<"sent"<<endl;
}
ros::spinOnce();
//}
}
