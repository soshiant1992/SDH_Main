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
#include <control_msgs/FollowJointTrajectoryResult.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>
//#include"armadillo"
// For the action client and follow trajectory goal
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <actionlib/client/simple_action_client.h>

// service file for the operation mode
#include <cob_srvs/SetString.h>

// Service file for the initialization
#include "std_srvs/Trigger.h"

#include <sdh_grasp/grasp_info.h>
#include <sdh_grasp/pre_grasp_pos_data.h>
#include"thread"
using namespace std;
//using namespace arma;
double current_angles[7] = { -60, -60, -60 , -60 , -60 , -60 , -60 };  /// used
int Pstrong[6] = {0 , 0, 0 , 0 , 0 , 0 } ;/// used
double d_theta[6] = {0 , 0, 0 , 0 , 0 , 0 } ;
string controller_mode ="not in any";
//int threshold[6];
double angles11[7];
std_msgs::Int8 feedback;
std_msgs::Float64MultiArray vel_dim;
double angles[7] = {0,0,0,0,0,0,0};
bool gripit=false;
bool openhand=true;
bool justproximal=true;
bool reachedproximal=false;
//bool reachedproximal=false;


//......................... Action Client
using actionlib::SimpleActionClient;

//mat sensordata,sensordata2,rosTime1,rosTime2;
string grasp_type;
//mat anglesmat;
SimpleActionClient<control_msgs::FollowJointTrajectoryAction>* traj_client;

ros::ServiceClient set_operation_mode_client;

ros::Publisher set_velocity;
ros::Publisher set_feedback;
//void domainloop();bool setvelocitymode();void backoff2();
long double  begin_t;
bool call_backoff=false;
bool did_backoff=false;
ros::ServiceClient recover;
ros::ServiceClient init;
ros::ServiceClient stop;
std_srvs::Trigger trigger ;

cob_srvs::SetString cobsrv ;
