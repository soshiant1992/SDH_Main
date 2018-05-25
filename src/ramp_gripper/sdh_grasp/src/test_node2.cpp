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
#include <math.h>

ros::Publisher pub;
ros::Publisher pub3;
int count11 =0;
using namespace std;



int main(int argc, char **argv)
{


    ros::init(argc, argv, "grasp_publisher");

    ros::NodeHandle n;
    count11 = 0;
    pub = n.advertise<sdh_grasp::grasp_info>("/sdh_grasp_control/grasp_goal", 1,true);
//    ros::Publisher pub2 = n. advertise<std_msgs::Int32MultiArray>("/sdh_grasp_control/force_threshold", 10);
//    pub3 = n. advertise<sdh_grasp::pre_grasp_pos_data>("/sdh_grasp_control/pre_grasp_config", 10);
//    ros::Subscriber sub = n.subscribe("/sdh_grasp_control/status",1, feedback);

        sdh_grasp::grasp_info abc;

        for (int var = 0; var < 2; ++var) {


        abc.type = "cylinder";
        pub.publish(abc);
        ros::Rate loop_rate(3);
        loop_rate.sleep();
        cout<<"sent"<<endl;
        ros::spinOnce();
        }
        //sleep(3);
//ros::spin();

}
