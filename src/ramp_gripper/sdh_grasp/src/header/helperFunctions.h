#include "headers.h"
bool setvelocitymode() {
//    std_srvs::Trigger trigger ;
   cout<< recover.call(trigger)<<endl;
    if (controller_mode.compare("velocity")==0) return true;
    std::stringstream ss;
    ss << "velocity" ;
    cobsrv.request.data = ss.str();


    if(set_operation_mode_client.call(cobsrv)){
        if(cobsrv.response.success){
            cout<<"$in_velocity_mode"<<endl;
            controller_mode="velocity";
            return true;
    }
    else {
     cout<<"%not_Velocity_mode"<<endl;
     setvelocitymode();
     usleep(100000);
        }}
}
///............                           Proportional Controller
/// //pro controller should depend on tactile and error and should return positiv and negative
void pro_controller(double kp, double error, double &d_theta)
{
    kp=kp/2;
    double threshold=200;
    if(error<=threshold)
        d_theta=kp/4;
    if(error<=threshold/2)
        d_theta=kp*2;
    if(error>threshold){
//        cout<<"error greater than threshold"<<error<<endl;
        d_theta=-.001;}
    if(gripit==false) d_theta=0;

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
              pro_controller(0.05, error[i], d_theta[i]) ; /// d_theta should be positive for proximal
if(reachedproximal)  pro_controller(0.0, (error[0]+error[4]+error[2])/3, d_theta[i]) ;
//            if(!justproximal)pro_controller(0.1, (error[3]+error[1]+error[5])/3, d_theta[i+1]) ; // then d_theta should be positive for distal
            if(!justproximal)pro_controller(0.05, error[i+1], d_theta[i+1]) ; // then d_theta should be positive for distal
            if(grasp_type!="cylinder"){ pro_controller(0.05, error[i+1], d_theta[i]) ;}

        }

        if(grasp_type=="cube"){ d_theta[0]=0;d_theta[1]=0;}
        ///////////////     Self- Collision Check

        for(int i = 1 ; i < 7; i = i +2 )
            if(current_angles[i] < -87 ||current_angles[i] > 87
                    || current_angles[5] >7 ||current_angles[3] >7||current_angles[1] >7
                    )     {   d_theta[i]=0;  }


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



bool setpositionmode(){

//        std_srvs::Trigger trigger ;
       cout<< recover.call(trigger)<<endl;
    if (controller_mode.compare("position")==0) return true;


    std::stringstream ss;
    ss << "position" ;
    cobsrv.request.data = ss.str();

    if(set_operation_mode_client.call(cobsrv)){
        if(cobsrv.response.success){
            controller_mode="position";
            cout<<"$in_Position_mode"<<endl;
            return true;
    }
    else {
            cout<<"%not_Position_mode"<<endl;
            setpositionmode();
            usleep(100000);
           }}
}


void showsomeimes(string hey,double number){

    int  rndd = rand() % 10;
    int  rndd2 = rand() % 20;
    if(rndd==rndd2)
        cout<<hey<<number<<endl;

}
bool randi(){

    int  rndd = rand() % 10;
    int  rndd2 = rand() % 20;
    if(rndd==rndd2)
        return true;
    else
        return false;

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
    goal.trajectory.points[ind].velocities[0] = 0.0;
    goal.trajectory.points[ind].velocities[1] = 0.0;
    goal.trajectory.points[ind].velocities[2] = 0.0;
    goal.trajectory.points[ind].velocities[3] = 0.0;
    goal.trajectory.points[ind].velocities[4] = 0.0;
    goal.trajectory.points[ind].velocities[5] = 0.0;
    goal.trajectory.points[ind].velocities[6] = 0.0;

    goal.trajectory.points[ind].time_from_start = ros::Duration(t);



    //we are done; return the goal
    return goal;
}
void pre_grasp_open(double angles[]) {

    double t  ;
//    ros::NodeHandle nn;
//    std_srvs::Trigger trigger ;
        int counter88=0;
        while(!recover.call(trigger) && (counter88<3)){
            counter88++;
            ROS_WARN("Failed to call service driver/recover");
            init.call(trigger);
       usleep(100000)     ;
           }
        if(counter88<3)
           ROS_INFO("driver recovered");
else
            ROS_INFO("driver recovery gave up");

   if(setpositionmode()){ t = 0.1 ;
    // Action Cl4ient for the joint Motion

    // wait for action server to come up
//    while(!traj_client->waitForServer(ros::Duration(0.3))){
//        ROS_INFO("Waiting for the joint_trajectory_action server");
//    }
//    ROS_INFO("Connected to the server");

    // Trajectory Following
    control_msgs::FollowJointTrajectoryGoal goal = armExtensionTrajectory(angles, t);
    goal.trajectory.header.stamp = ros::Time::now() ;
    traj_client->sendGoal(goal);
    //cout<<"++++++++++++++++++++++++++"<<traj_client->getResult().get("follow_joint_trajectory")<<endl;

}}
void backoff2(){
    for (int var = 1; var < 7; ++var) angles11[var]=(current_angles[var])*M_PI/180;


    int P=30;
    double min=.1;

//    setpositionmode();

//    usleep(250000)     ;
//    ros::ServiceClient client2 = nn.serviceClient<std_srvs::Trigger>("/driver/stop");
    stop.call(trigger);
//    while(!){
//        ROS_WARN("Failed to call service driver/stop");
//usleep(100000)     ;
//    }
//    usleep(1500000)     ;

//    std_srvs::Trigger trigger ;

//    ros::ServiceClient client1 = nn.serviceClient<std_srvs::Trigger>("/driver/recover");
////   cout<< client1.call(trigger)<<endl;
//    while(!client1.call(trigger)){
//        ROS_WARN("Failed to call service driver/init");
//usleep(100000)     ;
//    }
//    setpositionmode();
//if (grasp_type=="cube"){
//         angles11[5]=(current_angles[5]-min)*M_PI/180;
//        angles11[6]=(current_angles[6]+min)*M_PI/180;
//}
//if (grasp_type=="cylinder"){
//         angles11[1]=(current_angles[1]-min)*M_PI/180;
//        angles11[2]=(current_angles[2]+min)*M_PI/180;
//}

//if (grasp_type=="sphere" ){
//    int  rndd = rand() % 3;
//    if(rndd==0){
//         angles11[1]=(current_angles[1]-min)*M_PI/180;
//        angles11[2]=(current_angles[2]+min)*M_PI/180;
//}else
//    if(rndd==1){
//        angles11[3]=(current_angles[3]-min)*M_PI/180;
//        angles11[4]=(current_angles[4]+min)*M_PI/180;
//    }else
//    {
//        angles11[5]=(current_angles[5]-min)*M_PI/180;
//        angles11[6]=(current_angles[6]+min)*M_PI/180;
//    }

//}



//    angles11[0]=(current_angles[0]*3.1415/180);
//    if(abs(current_angles[0]-0)<5)
//        if(current_angles[0]-0<5)
//          angles11[0]=0.0;
//            if(90-current_angles[0]<5)
//        angles11[0]=89.9*M_PI/180;

//    pre_grasp_open( angles11);

}
