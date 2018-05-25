#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include <sdh_grasp/grasp_info.h>
#include <sdh_grasp/pre_grasp_pos_data.h>
#include <std_msgs/Int8.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

#include <math.h>
#include <schunk_sdh/TactileSensor.h>

using namespace std;
ros::Publisher pub;
ros::Publisher pub3;





int main(int argc, char **argv)
{


    ros::init(argc, argv, "grasp_publisher");

    ros::NodeHandle n;
//    pub = n.advertise<sdh_grasp::grasp_info>("/sdh_grasp_control/grasp_goal", 10);
//    ros::Publisher pub2 = n. advertise<std_msgs::Int32MultiArray>("/sdh_grasp_control/force_threshold", 10);
    pub3 = n. advertise<sdh_grasp::pre_grasp_pos_data>("/sdh_grasp_control/pre_grasp_config", 10);
//    ros::Subscriber sub = n.subscribe("/sdh_grasp_control/status",1, feedback);
//    ros::Subscriber sub3 = n.subscribe("/dsa_controller/tactile_data",1, tactilemaxprint);
//    ros::Subscriber sub4 = n.subscribe("/GuiObject",1, GUI_Object);
//     robot_is_ready= n.advertise<std_msgs::Bool>("/robot_is_ready",1000) ;

//     sleep(3);


     sdh_grasp::pre_grasp_pos_data xyz;

//     xyz.type = "spherical";
//     xyz.data.push_back((60*M_PI)/180);
//     xyz.data.push_back((-10*M_PI)/180);
//     xyz.data.push_back((6*M_PI)/180);
//     xyz.data.push_back((-10*M_PI)/180);
//     xyz.data.push_back((6*M_PI)/180);
//     xyz.data.push_back((-10*M_PI)/180);
//     xyz.data.push_back((6*M_PI)/180);
//     xyz.type = "cylinder";
//     xyz.data.push_back((0*M_PI)/180);
//     xyz.data.push_back((-40*M_PI)/180);
//     xyz.data.push_back((30*M_PI)/180);
//     xyz.data.push_back((-40*M_PI)/180);
//     xyz.data.push_back((30*M_PI)/180);
//     xyz.data.push_back((-40*M_PI)/180);
//     xyz.data.push_back((30*M_PI)/180);
          xyz.type = "cylinder";
          xyz.data.push_back((60*M_PI)/180);
          xyz.data.push_back((-15*M_PI)/180);
          xyz.data.push_back((10*M_PI)/180);
          xyz.data.push_back((-15*M_PI)/180);
          xyz.data.push_back((10*M_PI)/180);
          xyz.data.push_back((-15*M_PI)/180);
          xyz.data.push_back((10*M_PI)/180);
//          xyz.type = "cube";
//          xyz.data.push_back((89.9*M_PI)/180);
//          xyz.data.push_back((-89*M_PI)/180);
//          xyz.data.push_back((-89*M_PI)/180);
//          xyz.data.push_back((-10*M_PI)/180);
//          xyz.data.push_back((6*M_PI)/180);
//          xyz.data.push_back((-10*M_PI)/180);
//          xyz.data.push_back((6*M_PI)/180);

        for (int var = 0; var < 2; ++var) {

            pub3.publish(xyz);

        ros::Rate loop_rate(3);
        loop_rate.sleep();
        cout<<"sent"<<endl;
        ros::spinOnce();
        }

}
