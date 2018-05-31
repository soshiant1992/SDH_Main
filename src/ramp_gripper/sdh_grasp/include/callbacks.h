#include "helperFunctions.h"
///........................                Subscriber Function for the hand current configuration
void jointCallback(const sensor_msgs::JointState::ConstPtr& msg)
{

    if(msg->position.size()==7){
        for(size_t i = 0; i < msg->position.size(); i++)
        {
            current_angles[i] = msg->position[i]*180/3.1415;
        }

    }
}


void tactileCallback(const schunk_sdh::TactileSensor::ConstPtr& msg)
{
    //// Initialization.....
    for(int i = 0 ; i < 6 ; i++){Pstrong[i] = 0 ;}

    for(int sensorID=0; sensorID < 6; sensorID++)
    {
        int sz = msg->tactile_matrix[sensorID].cells_x * msg->tactile_matrix[sensorID].cells_y ;
        double  sensordata[sz];   long int mean54=0;int count336=0;
        for (int i = 0; i < sz; i++)
        {
            int val = msg->tactile_matrix[sensorID].tactile_array[i];
            sensordata[i]=val;
            if(Pstrong[sensorID] < val)
                Pstrong[sensorID] = val;

            if(val>0) {
                mean54+=val;
                count336++;
            }

        }

        if(Pstrong[sensorID]>0) {
            if (count336==0) {
                Pstrong[sensorID]=mean54;
            } else {
                Pstrong[sensorID]=mean54/count336;
            }
        }

    }
    Pstrong[0]/=10;
    Pstrong[2]+=5;
    Pstrong[2]*=10;


    double pmax=1000;

    if(grasp_type=="cube" && GRIP_VEL_TRIGGER && ((Pstrong[3]+Pstrong[5]>pmax)||((Pstrong[3]>pmax&&Pstrong[5]>pmax)))){
        GRIP_VEL_TRIGGER=false;
        call_backoff=true;
        backoff2();
    }
  else  if( grasp_type=="sphere" && GRIP_VEL_TRIGGER &&(
                (Pstrong[1]>pmax&&  Pstrong[3]>pmax&&  Pstrong[5]>pmax)||
                (Pstrong[0]>pmax&&  Pstrong[2]>pmax&&  Pstrong[4]>pmax)
                )){
        GRIP_VEL_TRIGGER=false;
        call_backoff=true;
        backoff2();
    }
  else  if( grasp_type=="cylinder" && GRIP_VEL_TRIGGER && reachedproximal==false &&(

              Pstrong[0]>pmax/2&&  Pstrong[2]>pmax/2&&  Pstrong[4]>pmax/2  )){
        reachedproximal=true;

    }
   else if( grasp_type=="cylinder" && GRIP_VEL_TRIGGER &&(
                Pstrong[1]>pmax &&  Pstrong[3]>pmax &&  Pstrong[5]>pmax
            /*&&  Pstrong[0]>10&&  Pstrong[2]>10&&  Pstrong[4]>10 */ )){
        GRIP_VEL_TRIGGER=false;cout<<"GRIP_VEL_TRIGGER=false"<<endl;
        call_backoff=true;

          backoff2();
    }
//cout<<GRIP_VEL_TRIGGER<<endl;




}




void backoff(const sdh_grasp::pre_grasp_pos_data& msg){
    cout<<"gotbackoff"<<endl;
    backoff2();
}

void grasp_type_callback(const sdh_grasp::grasp_info& msg) {
//    ros::NodeHandle nn;
//    std_srvs::Trigger trigger ;
    int counter88=0;
    while(!_recover_sc.call(trigger) && (counter88<3)){
        counter88++;
        ROS_WARN("Failed to call service driver/recover");
   usleep(1000000)     ;
   _init_sc.call(trigger);

       }
    if(counter88<3)
       ROS_INFO("driver recovered");
else
        ROS_INFO("driver recovery gave up");


    setvelocitymode();
    GRIP_VEL_TRIGGER=true;
    GRIP_POS_TRIGGER=false;reachedproximal=false;
    //    reachedproximal=false;
    if(msg.type=="cylinder")justproximal=false;
    grasp_type=msg.type;
    //            feedback.data =1;
    //            set_feedback.publish(feedback);


}
void stop_callback(const sdh_grasp::grasp_info& msg) {
    setvelocitymode();
    GRIP_VEL_TRIGGER=false;
    GRIP_POS_TRIGGER=false;reachedproximal=false;
    //    reachedproximal=false;
    if(msg.type=="cylinder")justproximal=false;
    grasp_type=msg.type;
    cout<<"got the stop it message"<<endl;

    //            feedback.data =1;
    //            set_feedback.publish(feedback);
//    mat saved_on_what_seq=zeros(1);
//    saved_on_what_seq(0)=ros::Time::now().toSec()-begin_t;
//    saved_on_what_seq.save("c137",raw_ascii);

}
void grasp_pos_callback(const sdh_grasp::pre_grasp_pos_data& msg) {

    GRIP_POS_TRIGGER=true;
    GRIP_VEL_TRIGGER=false;
    justproximal=true;

    //    reachedproximal=false;
    cout<<"pregrasp recieved ##########################################################3"<<endl;
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







void keepbackingoff(const control_msgs::FollowJointTrajectoryActionResult& msg){
//    bool nordic=true;
//    for (int var = 1; var < 7; var++) {
//         if(abs(angles11[var]*180/M_PI-current_angles[var]>.2))nordic=false;
//    }

//    cout<<" keepbackingoff  "<<Pstrong[0]+Pstrong[2]+Pstrong[4]+Pstrong[1]+Pstrong[3]+Pstrong[5]<<endl;
//  if(!openhand)/*if(nordic)*/ if(Pstrong[0]>200||Pstrong[2]>200||Pstrong[4]>200||Pstrong[1]>200||Pstrong[3]>200||Pstrong[5]>200)call_backoff;
usleep(250000);
//sleep(1);
did_backoff=true;
cout<<" keepbackingoff  "<<endl;

}

