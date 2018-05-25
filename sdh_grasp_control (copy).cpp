#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "std_msgs/String.h"
#include "string.h"

// For getting tactile feedback
#include <schunk_sdh/TactileSensor.h>
#include <schunk_sdh/TactileMatrix.h>

// For getting joint angles
#include "sensor_msgs/JointState.h"

// For publishing the finger joint velocities
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>
#include"armadillo"
// For the action client and follow trajectory goal 
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <actionlib/client/simple_action_client.h>

// service file for the operation mode
#include <cob_srvs/SetString.h>

// Service file for the initialization
#include "std_srvs/Trigger.h"

#include <sdh_grasp/grasp_info.h>
#include <sdh_grasp/pre_grasp_pos_data.h>


//................. Global Varibles

double current_angles[7] = { -60, -60, -60 , -60 , -60 , -60 , -60 };  /// used
int Pstrong[6] = {0 , 0, 0 , 0 , 0 , 0 } ;/// used
double d_theta[6] = {0 , 0, 0 , 0 , 0 , 0 } ;

int threshold[6];


std_msgs::Int8 feedback;
std_msgs::Float64MultiArray vel_dim;

double lateral_angles[7] = {0,0,0,0,0,0,0};
double spherical_angles[7] = {0,0,0,0,0,0,0};
double pinch_angles[7] = {0,0,0,0,0,0,0};
double custom_angles[7] = {0,0,0,0,0,0,0};
bool gripit=false;
//......................... Action Client
using actionlib::SimpleActionClient;
using namespace std;
using namespace arma;
mat sensordata;

SimpleActionClient<control_msgs::FollowJointTrajectoryAction>* traj_client;

ros::ServiceClient client;

ros::Publisher set_velocity;
ros::Publisher set_feedback;
void domainloop();
///............                           Proportional Controller 
/// //pro controller should depend on tactile and error and should return positiv and negative
void pro_controller(double kp, double error, double &d_theta)
{
if(error<-100)
  cout<<error<<endl;

    if(error>0)
        d_theta=.1;
    else {if(error>-1000)
        d_theta=0;
        else
        d_theta=-.05;}
//    d_theta = (error * kp)/1000 ;
}

///........................                Subscriber Function for the hand current configuration
void jointCallback(const sensor_msgs::JointState::ConstPtr& msg)
 {
         for(size_t i = 0; i < msg->position.size(); ++i)
         {
               if(i != 0)
                    current_angles[i] = msg->position[i]*180/3.14;
         }
 }




void tactileCallback(const schunk_sdh::TactileSensor::ConstPtr& msg)
{
    int  rndd = rand() % 10;
    int  rndd2 = rand() % 20;

  if(rndd==rndd2)
cout<<"tactilecalled  "<<rndd<<" gripit = "<<gripit<<endl;

//// Initialization.....
    for(int i = 0 ; i < 6 ; i++)
    {
   Pstrong[i] = 0 ;
    }

    for(int sensorID=0; sensorID < 6; sensorID++)
    {
        int sz = msg->tactile_matrix[sensorID].cells_x * msg->tactile_matrix[sensorID].cells_y ;
        sensordata.zeros(sz);

        for (int i = 0; i < sz; i++)
        {
        int val = msg->tactile_matrix[sensorID].tactile_array[i];
        sensordata(i)=val;
        if(Pstrong[sensorID] < val)
                Pstrong[sensorID] = val ;
       }
        if(Pstrong[sensorID]>0)
        Pstrong[sensorID]=mean(nonzeros(sensordata));
//        if(Pstrong[sensorID]>3)//cout<<Pstrong[sensorID]<<endl;
//        cout<<sensordata.st()<<endl;
   }
if(Pstrong[1]!=0&&Pstrong[3]!=0&&Pstrong[5]!=0)gripit=false;
if(Pstrong[0]!=0&&Pstrong[2]!=0&&Pstrong[4]!=0)gripit=false;

   if(gripit) domainloop();

}



///.....................  Function for hand desired configurtion
/// Note: Velocities can be zero only... the server node code supports only tht..
control_msgs::FollowJointTrajectoryGoal armExtensionTrajectory(double* angles, double t)
  {
    //our goal variable
    control_msgs::FollowJointTrajectoryGoal goal;

    // First, the joint names, which apply to all waypoints
    goal.trajectory.joint_names.push_back("sdh_knuckle_joint");
    goal.trajectory.joint_names.push_back("sdh_thumb_2_joint");
    goal.trajectory.joint_names.push_back("sdh_thumb_3_joint");
    goal.trajectory.joint_names.push_back("sdh_finger_12_joint");
    goal.trajectory.joint_names.push_back("sdh_finger_13_joint");
    goal.trajectory.joint_names.push_back("sdh_finger_22_joint");
    goal.trajectory.joint_names.push_back("sdh_finger_23_joint");

    // We will have two waypoints in this goal trajectory
    goal.trajectory.points.resize(1);

    // First trajectory point
    // Positions
    int ind = 0;
    goal.trajectory.points[ind].positions.resize(7);
    goal.trajectory.points[ind].positions[0] = angles[0];
    goal.trajectory.points[ind].positions[1] = angles[1];
    goal.trajectory.points[ind].positions[2] = angles[2];
    goal.trajectory.points[ind].positions[3] = angles[3];
    goal.trajectory.points[ind].positions[4] = angles[4];
    goal.trajectory.points[ind].positions[5] = angles[5];
    goal.trajectory.points[ind].positions[6] = angles[6]; 
    // Velocities
    goal.trajectory.points[ind].velocities.resize(7);
    goal.trajectory.points[ind].velocities[0] = 0;
    goal.trajectory.points[ind].velocities[1] = 0;
    goal.trajectory.points[ind].velocities[2] = 0;
    goal.trajectory.points[ind].velocities[3] = 0;
    goal.trajectory.points[ind].velocities[4] = 0;
    goal.trajectory.points[ind].velocities[5] = 0;
    goal.trajectory.points[ind].velocities[6] = 0;
    
    goal.trajectory.points[ind].time_from_start = ros::Duration(1.00);

    

    //we are done; return the goal
    return goal;
  }






  void pre_grasp_open(double angles[])
  {

      // degree conversion to radians
      double degtorad = 3.1415/180 ;

      if(angles[0]<0)
          angles[0] =0;

      else if(angles[0]>(90/degtorad))
          angles[0] =90*degtorad;

      else
            angles[0] = angles[0];

      for(int i=1; i<7; i++)
      {

          if(angles[i]<(-85/degtorad))
              angles[i] = -85/degtorad;
          if(angles[i] >(85/degtorad))
              angles[i] = 85/degtorad;


      }

      double t = 1 ;

      cob_srvs::SetString srv ;

      std::stringstream ss;
      ss << "position" ;

      srv.request.data = ss.str();


      t = 1 ;


      // Action Cl4ient for the joint Motion
          traj_client = new SimpleActionClient<control_msgs::FollowJointTrajectoryAction>("/joint_trajectory_controller/follow_joint_trajectory",true);

      // wait for action server to come up
          while(!traj_client->waitForServer(ros::Duration(5.0))){
            ROS_INFO("Waiting for the joint_trajectory_action server");
          }
          ROS_INFO("Connected to the server");

      // Trajectory Following
          control_msgs::FollowJointTrajectoryGoal goal = armExtensionTrajectory(angles, t);
          goal.trajectory.header.stamp = ros::Time::now() ;
          traj_client->sendGoal(goal);


  }


  void grasp_type_callback(const sdh_grasp::grasp_info& msg)
  {
gripit=true;


//            feedback.data =1;
//            set_feedback.publish(feedback);


  }



void grasp_pos_callback(const sdh_grasp::pre_grasp_pos_data& msg){

    std::string grip1 ("lateral");
    std::string grip2 ("spherical");
    std::string grip3 ("pinch");
    std::string grip4 ("custom_config");
    std::string s = msg.type;

    if(grip1.compare(s) == 0)
    {

        lateral_angles[0] = double(msg.data[0]);
        lateral_angles[1] = double(msg.data[1]);
        lateral_angles[2] = double(msg.data[2]);
        lateral_angles[3] = double(msg.data[3]);
        lateral_angles[4] = double(msg.data[4]);
        lateral_angles[5] = double(msg.data[5]);
        lateral_angles[6] = double(msg.data[6]);
    }
    if(grip2.compare(s) == 0)
    {
        spherical_angles[0] = double(msg.data[0]);
        spherical_angles[1] = double(msg.data[1]);
        spherical_angles[2] = double(msg.data[2]);
        spherical_angles[3] = double(msg.data[3]);
        spherical_angles[4] = double(msg.data[4]);
        spherical_angles[5] = double(msg.data[5]);
        spherical_angles[6] = double(msg.data[6]);
    }
    if(grip3.compare(s) == 0)
    {
        pinch_angles[0] = double(msg.data[0]);
        pinch_angles[1] = double(msg.data[1]);
        pinch_angles[2] = double(msg.data[2]);
        pinch_angles[3] = double(msg.data[3]);
        pinch_angles[4] = double(msg.data[4]);
        pinch_angles[5] = double(msg.data[5]);
        pinch_angles[6] = double(msg.data[6]);
    }
    if(grip4.compare(s) == 0)
    {
        custom_angles[0] = double(msg.data[0]);
        custom_angles[1] = double(msg.data[1]);
        custom_angles[2] = double(msg.data[2]);
        custom_angles[3] = double(msg.data[3]);
        custom_angles[4] = double(msg.data[4]);
        custom_angles[5] = double(msg.data[5]);
        custom_angles[6] = double(msg.data[6]);
    }



}

void domainloop(){

if(gripit){
//    cob_srvs::SetString srv ;
//    std::stringstream ss;
//    ss << "velocity" ;
//    srv.request.data = ss.str();
//    client.call(srv);

        int error[6];
        // variable to halt the finger links

      int  rndd = rand() % 10;
      int  rndd2 = rand() % 20;

    if(rndd==rndd2)   // ROS_INFO("in themainloop");
cout<<"in the main loop"<<rndd<<endl;


        for( int i =0; i< 6 ; i++)d_theta[i] = 0;


    ///                        Calculation of tactile Error values:
        for(int i = 0 ; i < 6 ; i ++) error[i] = threshold[i] - Pstrong[i]  ;/// Distal Values

int backdown=666;
         for(int i = 0; i < 6 ; i = i+2)
        {
             pro_controller(0.055, error[i], d_theta[i]) ; /// d_theta should be positive for proximal
//            pro_controller(0.072, error[i+1], d_theta[i+1]) ; // then d_theta should be positive for distal
            if(d_theta[i]<0)backdown=i;
        }
         if(backdown!=666)for (int var = 0; var < 6; ++var) {
             if(d_theta[var]>0)d_theta[var]=0;
         }

    ///////////////     Self- Collision Check

        for(int i = 1 ; i < 7; i = i +2 )
        if(current_angles[i] < -87 ||current_angles[i] > 87)     {   d_theta[i]=0;  }

    //////      SDH-Motion Version 2.0
    //// now d_theta represents velocity

    vel_dim.data[0] = 0 ;
    for(int i = 0 ; i < 6 ; i++) vel_dim.data[i+1] = d_theta[i];

    set_velocity.publish(vel_dim) ;

        ros::spin();


}}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "sdh_grasp_control");
    ros::NodeHandle nn;
    // Service Client for initizalization
    ros::ServiceClient client1 = nn.serviceClient<std_srvs::Trigger>("/driver/init");
    std_srvs::Trigger srv1 ;
    vel_dim.data.resize(7);
    vel_dim.data[0] = 0 ;
    // Client1 calling the service
    if (client1.call(srv1))
    {
    }
      else
    {
     ROS_ERROR("Failed to call service driver/init");
     return 1;
    }

    threshold[0] = threshold[1] = 500;
    threshold[2] = threshold[3] = 2;
    threshold[4] = threshold[5] = 100;


    ros::NodeHandle v ("~");

       {     v.getParam("Lateral_0",lateral_angles[0]);
            v.getParam("Lateral_1",lateral_angles[1]);
            v.getParam("Lateral_2",lateral_angles[2]);
            v.getParam("Lateral_3",lateral_angles[3]);
            v.getParam("Lateral_4",lateral_angles[4]);
            v.getParam("Lateral_5",lateral_angles[5]);
            v.getParam("Lateral_6",lateral_angles[6]);

            v.getParam("Spherical_0",spherical_angles[0]);
            v.getParam("Spherical_1",spherical_angles[1]);
            v.getParam("Spherical_2",spherical_angles[2]);
            v.getParam("Spherical_3",spherical_angles[3]);
            v.getParam("Spherical_4",spherical_angles[4]);
            v.getParam("Spherical_5",spherical_angles[5]);
            v.getParam("Spherical_6",spherical_angles[6]);


            v.getParam("Pinch_0",pinch_angles[0]);
            v.getParam("Pinch_1",pinch_angles[1]);
            v.getParam("Pinch_2",pinch_angles[2]);
            v.getParam("Pinch_3",pinch_angles[3]);
            v.getParam("Pinch_4",pinch_angles[4]);
            v.getParam("Pinch_5",pinch_angles[5]);
            v.getParam("Pinch_6",pinch_angles[6]);
}


    client = nn.serviceClient<cob_srvs::SetString>("/driver/set_operation_mode");
    ros::Subscriber sub = nn.subscribe("/joint_states", 1000, jointCallback);
    ros::Subscriber sub1 = nn.subscribe("/dsa_controller/tactile_data", 10, tactileCallback);
    set_velocity = nn.advertise<std_msgs::Float64MultiArray> ("/joint_group_velocity_controller/command", 1);
//    ros::Subscriber pre_grasp_pos = nn.subscribe("/sdh_grasp_control/pre_grasp_config" , 2 , grasp_pos_callback);
    ros::Subscriber grasp_type  = nn.subscribe("/sdh_grasp_control/grasp_goal" , 1 , grasp_type_callback);
//    set_feedback = nn.advertise<std_msgs::Int8>("/sdh_grasp_control/status" , 1);
//  ros::spin();
    ros::Rate loop_rate(50);

    while(ros::ok()) {
        cob_srvs::SetString srv ;
        std::stringstream ss;
        ss << "velocity" ;
        srv.request.data = ss.str();
        client.call(srv);
       if(gripit) {

           set_velocity.publish(vel_dim) ;
       }

        ros::spinOnce();
        loop_rate.sleep();

    }
    return 0;
}
