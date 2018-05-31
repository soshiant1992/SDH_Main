
#include <callbacks.h>


int main(int argc, char **argv)
{

    grasp_type="cylinder";
    ros::init(argc, argv, "sdh_grasp_control");
    ros::NodeHandle _nh ("~");

    // Service Client for initizalization
     _init_sc = _nh.serviceClient<std_srvs::Trigger>("/driver/init");
     _recover_sc=_nh.serviceClient<std_srvs::Trigger>("/driver/recover");
     _stop_sc=_nh.serviceClient<std_srvs::Trigger>("/driver/stop");
     traj_client = new SimpleActionClient<control_msgs::FollowJointTrajectoryAction>("/joint_trajectory_controller/follow_joint_trajectory",true);
     _sdh_velocity_pub = _nh.advertise<std_msgs::Float64MultiArray> ("/joint_group_velocity_controller/command", 1);
     set_operation_mode_client = _nh.serviceClient<cob_srvs::SetString>("/driver/set_operation_mode");

    std_srvs::Trigger triger ;
    vel_dim.data.resize(7);
    vel_dim.data[0] = 0 ;
    // Client1 calling the service
    while (!_init_sc.call(triger)){
        usleep(500000);
        ROS_ERROR("Failed to call service driver/init");
    }

//*  Mike removed because these do not appear to be used.
// * Domains for /backoff & /stop_it should change to 'sdh_grasp_cotnrol' namespace
// *
    ros::Subscriber joint_states = _nh.subscribe("/joint_states", 1, jointCallback);
    ros::Subscriber tactile_data = _nh.subscribe("/dsa_controller/tactile_data", 1, tactileCallback);
    ros::Subscriber backoffsub = _nh.subscribe("/backoff", 1, backoff);
    ros::Subscriber pre_grasp_pos = _nh.subscribe("/sdh_grasp_control/pre_grasp_config" , 1 , grasp_pos_callback);
    ros::Subscriber grasp_type  = _nh.subscribe("/sdh_grasp_control/grasp_goal" , 1 , grasp_type_callback);
    ros::Subscriber stop_it  = _nh.subscribe("/stop_it" , 1 , stop_callback);

    ros::Rate loop_rate(100);
    ros::AsyncSpinner spinner(4); // Use 4 threads
    spinner.start();
    while(ros::ok()) {
//        ros::spinOnce();
        //GRIP_POS_TRIGGER would be more secure if we had an interface to access / change this
        if(!GRIP_POS_TRIGGER)
            autoGrasp();
        loop_rate.sleep();
    }

}
