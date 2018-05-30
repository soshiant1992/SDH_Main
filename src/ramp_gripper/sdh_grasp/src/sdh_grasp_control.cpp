
#include "header/callbacks.h"




int main(int argc, char **argv)
{
//    anglesmat=zeros(6,1);
//    sensordata2=zeros(6,1);
    grasp_type="cylinder";
//    rosTime1=zeros(1);
//    rosTime2=zeros(1);
    ros::init(argc, argv, "sdh_grasp_control");
    ros::NodeHandle NH ("~");
    // Service Client for initizalization
     init = NH.serviceClient<std_srvs::Trigger>("/driver/init");
     recover=NH.serviceClient<std_srvs::Trigger>("/driver/recover");
     stop=NH.serviceClient<std_srvs::Trigger>("/driver/stop");
     traj_client = new SimpleActionClient<control_msgs::FollowJointTrajectoryAction>("/joint_trajectory_controller/follow_joint_trajectory",true);
     set_velocity = NH.advertise<std_msgs::Float64MultiArray> ("/joint_group_velocity_controller/command", 1);
     set_operation_mode_client = NH.serviceClient<cob_srvs::SetString>("/driver/set_operation_mode");

    std_srvs::Trigger triger ;
    vel_dim.data.resize(7);
    vel_dim.data[0] = 0 ;
    // Client1 calling the service
    while (!init.call(triger)){
    usleep(300000);
        ROS_ERROR("Failed to call service driver/init");
    }


    ros::Subscriber joint_states = NH.subscribe("/joint_states", 1, jointCallback);
    ros::Subscriber tactile_data = NH.subscribe("/dsa_controller/tactile_data", 1, tactileCallback);
    ros::Subscriber backoffsub = NH.subscribe("/backoff", 1, backoff);
    ros::Subscriber pre_grasp_pos = NH.subscribe("/sdh_grasp_control/pre_grasp_config" , 1 , grasp_pos_callback);
    ros::Subscriber grasp_type  = NH.subscribe("/sdh_grasp_control/grasp_goal" , 1 , grasp_type_callback);
    ros::Subscriber stop_it  = NH.subscribe("/stop_it" , 1 , stop_callback);

    ros::Rate loop_rate(100);
begin_t= ros::Time::now().toSec();
ros::AsyncSpinner spinner(4); // Use 4 threads
    spinner.start();
    while(ros::ok()) {
//        ros::spinOnce();
        if(!openhand)  domainloop();
        loop_rate.sleep();
    }

}
