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
#include"thread"
//#include ""
using namespace std;
using namespace arma;
//................. Global Varibles
//const sdh_grasp::pre_grasp_pos_data& dummiemsg;
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

mat sensordata,sensordata2;
string grasp_type;
mat anglesmat;
SimpleActionClient<control_msgs::FollowJointTrajectoryAction>* traj_client;

ros::ServiceClient client;

ros::Publisher set_velocity;
ros::Publisher set_feedback;
void domainloop();bool setvelocitymode();void backoff2();


bool setpositionmode(){
    if (controller_mode.compare("position")==0) return true;

    cob_srvs::SetString srv ;
    std::stringstream ss;
    ss << "position" ;
    srv.request.data = ss.str();

    if(client.call(srv)){
        if(srv.response.success){
            controller_mode="position";
            cout<<"$in_Position_mode"<<endl;
            return true;
    }
    else {
            cout<<"%not_Position_mode"<<endl;
            setpositionmode();
           }}
}


void showsomeimes(string hey,double number){

    int  rndd = rand() % 10;
    int  rndd2 = rand() % 20;
    if(rndd==rndd2)
        cout<<hey<<number<<endl;

}
///............                           Proportional Controller
/// //pro controller should depend on tactile and error and should return positiv and negative
void pro_controller(double kp, double error, double &d_theta)
{
    double threshold=20;
    if(error<=threshold)
        d_theta=kp;
    if(error>threshold){
//        cout<<"error greater than threshold"<<error<<endl;
        d_theta=0;}
    if(gripit==false) d_theta=0;

}

///........................                Subscriber Function for the hand current configuration
void jointCallback(const sensor_msgs::JointState::ConstPtr& msg)
{
    int  rndd = rand() % 10;
    int  rndd2 = rand() % 20;
    if(msg->position.size()==7){
        for(size_t i = 0; i < msg->position.size(); i++)
        {
            current_angles[i] = msg->position[i]*180/3.1415;
if(i!=0)anglesmat(i-1,anglesmat.n_cols-1)=current_angles[i] ;
        }
        anglesmat.insert_cols(anglesmat.n_cols,1);
if(rndd==rndd2)
anglesmat.save("anglesc137",raw_ascii);
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
sensordata=zeros(sz);
        for (int i = 0; i < sz; i++)
        {
            int val = msg->tactile_matrix[sensorID].tactile_array[i];
            sensordata(i)=val;
            if(Pstrong[sensorID] < val)
                Pstrong[sensorID] = val ;
        }
        if(Pstrong[sensorID]>0)
           { Pstrong[sensorID]=mean(nonzeros(sensordata));
            sensordata2(sensorID,sensordata2.n_cols-1)=Pstrong[sensorID];
//         cout<<sensorID<<"===="<<Pstrong[sensorID]<<endl;
        }
    }
    sensordata2.insert_cols(sensordata2.n_cols,1);
    if(rndd==rndd2)
    sensordata2.save("sensorc137",raw_ascii);

    if(Pstrong[0]+Pstrong[2]+Pstrong[4]>3)
    {
//        cout<<"sensoraftercontact_proximal"<<Pstrong[0]+Pstrong[2]+Pstrong[4]<<endl;
//        cout<<"sensoraftercontact_distal"<<Pstrong[1]+Pstrong[3]+Pstrong[5]<<endl;
    }
    if(grasp_type=="cube" && gripit && (Pstrong[3]+Pstrong[5]>20)){
        gripit=false;
       // backoff2();
    }
    if(gripit && Pstrong[1]>0&&  Pstrong[3]>0&&  Pstrong[5]>0&&
            (Pstrong[1]
            + Pstrong[3]
            +Pstrong[5]>30)
            ){
        gripit=false;
        mat saved_on_what_seq=zeros(2);
        saved_on_what_seq(0)=anglesmat.n_cols;
        saved_on_what_seq(1)=sensordata2.n_cols;
        saved_on_what_seq.save("c137",raw_ascii);
      //if(grasp_type!="sphere")  backoff2();
    }
    if(gripit && Pstrong[0]+Pstrong[2]+Pstrong[4]>30){
        reachedproximal=true;
    }else reachedproximal=false;

    if(!openhand)  domainloop();
}



///.....................  Function for hand desired configurtion
/// Note: Velocities can be zero only... the server node code supports only tht..
control_msgs::FollowJointTrajectoryGoal armExtensionTrajectory(double* angles, double t) {
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

    goal.trajectory.points[ind].time_from_start = ros::Duration(0.4);



    //we are done; return the goal
    return goal;
}






void pre_grasp_open(double angles[]) {

    double t = 1 ;

   if(setpositionmode()){ t = 1 ;
    // Action Cl4ient for the joint Motion
    traj_client = new SimpleActionClient<control_msgs::FollowJointTrajectoryAction>("/joint_trajectory_controller/follow_joint_trajectory",true);

    // wait for action server to come up
    while(!traj_client->waitForServer(ros::Duration(1.0))){
        ROS_INFO("Waiting for the joint_trajectory_action server");
    }
//    ROS_INFO("Connected to the server");

    // Trajectory Following
    control_msgs::FollowJointTrajectoryGoal goal = armExtensionTrajectory(angles, t);
    goal.trajectory.header.stamp = ros::Time::now() ;
    traj_client->sendGoal(goal);
    //cout<<"++++++++++++++++++++++++++"<<traj_client->getResult().get("follow_joint_trajectory")<<endl;

}}

void backoff2(){
    for (int var = 1; var < 7; ++var) angles11[var]=(current_angles[var])*M_PI/180;

    int P=-1;
    double min=.3;
  if(Pstrong[0]>P&&Pstrong[1]>P){  angles11[1]=(current_angles[1]-min)*M_PI/180;
    angles11[2]=(current_angles[2]+min)*M_PI/180;}
  if(Pstrong[2]>P&&Pstrong[3]>P){  angles11[3]=(current_angles[3]-min)*M_PI/180;
    angles11[4]=(current_angles[4]+min)*M_PI/180;}
   if(Pstrong[4]>P&&Pstrong[5]>P){  angles11[5]=(current_angles[5]-min)*M_PI/180;
    angles11[6]=(current_angles[6]+min)*M_PI/180;}


    angles11[0]=(current_angles[0]*3.1415/180);
    if(abs(current_angles[0]-0)<5)
        if(current_angles[0]-0<5)
          angles11[0]=0.0;
            if(90-current_angles[0]<5)
        angles11[0]=89.9*M_PI/180;

    pre_grasp_open( angles11);

}
//void keepbackingoff(const control_msgs::FollowJointTrajectoryActionResult& msg){
//    bool nordic=true;
//    for (int var = 1; var < 7; var++) {
//         if(abs(angles11[var]*180/M_PI-current_angles[var]>.2))nordic=false;
//    }

//    cout<<" keepbackingoff  "<<Pstrong[0]+Pstrong[2]+Pstrong[4]+Pstrong[1]+Pstrong[3]+Pstrong[5]<<endl;
//  if(!openhand)if(nordic) if(Pstrong[0]>200||Pstrong[2]>200||Pstrong[4]>200||Pstrong[1]>200||Pstrong[3]>200||Pstrong[5]>200)backoff2();
//}



void backoff(const sdh_grasp::pre_grasp_pos_data& msg){
    cout<<"gotbackoff"<<endl;
    backoff2();
}
void grasp_type_callback(const sdh_grasp::grasp_info& msg) {
    setvelocitymode();
    gripit=true;
    openhand=false;reachedproximal=false;
    //    reachedproximal=false;
    if(msg.type=="cylinder")justproximal=false;
grasp_type=msg.type;
    //            feedback.data =1;
    //            set_feedback.publish(feedback);


}



void grasp_pos_callback(const sdh_grasp::pre_grasp_pos_data& msg) {

    openhand=true;
    gripit=false;
    justproximal=true;

    //    reachedproximal=false;
    cout<<"pregrasp"<<endl;
grasp_type=msg.type;
    angles[0] = double(msg.data[0]);
    angles[1] = double(msg.data[1]);
    angles[2] = double(msg.data[2]);
    angles[3] = double(msg.data[3]);
    angles[4] = double(msg.data[4]);
    angles[5] = double(msg.data[5]);
    angles[6] = double(msg.data[6]);
    cout<<grasp_type<<endl;

    pre_grasp_open(angles);

}

void domainloop() {


    if(gripit){
        int error[6];
        // variable to halt the finger links




        for( int i =0; i< 6 ; i++)d_theta[i] = 0;


        ///                        Calculation of tactile Error values:
        for(int i = 0 ; i < 6 ; i ++) error[i] = Pstrong[i]  ;/// Distal Values

        for(int i = 0; i < 6 ; i = i+2)
        {
//              pro_controller(0.1, (error[0]+error[4]+error[2])/3, d_theta[i]) ; /// d_theta should be positive for proximal
              pro_controller(0.1, error[i], d_theta[i]) ; /// d_theta should be positive for proximal
if(reachedproximal)  pro_controller(0.0, (error[0]+error[4]+error[2])/3, d_theta[i]) ;
//            if(!justproximal)pro_controller(0.1, (error[3]+error[1]+error[5])/3, d_theta[i+1]) ; // then d_theta should be positive for distal
            if(!justproximal)pro_controller(0.1, error[i+1], d_theta[i+1]) ; // then d_theta should be positive for distal

        }

        if(grasp_type=="cube"){ d_theta[0]=0;d_theta[1]=0;}
        ///////////////     Self- Collision Check

        for(int i = 1 ; i < 7; i = i +2 )
            if(current_angles[i] < -87 ||current_angles[i] > 87)     {   d_theta[i]=0;  }

        //////      SDH-Motion Version 2.0
        //// now d_theta represents velocity

        vel_dim.data[0] = 0 ;
        for(int i = 0 ; i < 6 ; i++) vel_dim.data[i+1] = d_theta[i];
//cout<<vel_dim.data[1] <<vel_dim.data[2] <<vel_dim.data[3] <<vel_dim.data[4] <<vel_dim.data[5] <<endl;
        set_velocity.publish(vel_dim) ;

    }
    else if(controller_mode=="velocity"){
        vel_dim.data[0] = 0 ;
        for(int i = 0 ; i < 6 ; i++) vel_dim.data[i+1] = 0;

        set_velocity.publish(vel_dim) ;

    }

}

bool setvelocitymode() {
    if (controller_mode.compare("velocity")==0) return true;
    cob_srvs::SetString srv ;
    std::stringstream ss;
    ss << "velocity" ;
    srv.request.data = ss.str();


    if(client.call(srv)){
        if(srv.response.success){
            cout<<"$in_velocity_mode"<<endl;
            controller_mode="velocity";
            return true;
    }
    else {

     cout<<"%not_Velocity_mode"<<endl;
     setvelocitymode();
        }}
}
int main(int argc, char **argv)
{   anglesmat=zeros(6,1);
    sensordata2=zeros(6,1);
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

    //    threshold[0] = threshold[1] = 500;
    //    threshold[2] = threshold[3] = 2;
    //    threshold[4] = threshold[5] = 100;

//    threshold[0] = threshold[1] = 20;
//    threshold[2] = threshold[3] = 20;
//    threshold[4] = threshold[5] = 20;

    ros::NodeHandle v ("~");

    client = nn.serviceClient<cob_srvs::SetString>("/driver/set_operation_mode");
    ros::Subscriber sub = nn.subscribe("/joint_states", 2000, jointCallback);
    ros::Subscriber sub1 = nn.subscribe("/dsa_controller/tactile_data", 1, tactileCallback);
    ros::Subscriber sub2 = nn.subscribe("/backoff", 1, backoff);
//    ros::Subscriber sub3 = nn.subscribe("/joint_trajectory_controller/follow_joint_trajectory/result", 1, keepbackingoff);

    set_velocity = nn.advertise<std_msgs::Float64MultiArray> ("/joint_group_velocity_controller/command", 1);
    ros::Subscriber pre_grasp_pos = nn.subscribe("/sdh_grasp_control/pre_grasp_config" , 1 , grasp_pos_callback);
    ros::Subscriber grasp_type  = nn.subscribe("/sdh_grasp_control/grasp_goal" , 1 , grasp_type_callback);
    //    set_feedback = nn.advertise<std_msgs::Int8>("/sdh_grasp_control/status" , 1);
    //  ros::spin();
    //    ros::Rate loop_rate(1);

    //    setvelocitymode();
    ros::Rate loop_rate(100);

    while(ros::ok()) {




        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
