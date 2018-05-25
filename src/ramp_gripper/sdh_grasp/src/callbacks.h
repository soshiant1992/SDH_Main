#include "helperFunctions.h"
///........................                Subscriber Function for the hand current configuration
void jointCallback(const sensor_msgs::JointState::ConstPtr& msg)
{

    if(msg->position.size()==7){
        for(size_t i = 0; i < msg->position.size(); i++)
        {
            current_angles[i] = msg->position[i]*180/3.1415;
            if(i!=0)anglesmat(i-1,anglesmat.n_cols-1)=current_angles[i] ;
        }
        anglesmat.insert_cols(anglesmat.n_cols,1);
        rosTime1.insert_cols(rosTime1.n_cols,1);
        rosTime1(rosTime1.n_cols-1)=ros::Time::now().toSec()-begin_t;

//        if(randi())
//        {anglesmat.save("anglesc137",raw_ascii);
//        rosTime1.save("rosTime1",raw_ascii);}
//if(call_backoff){
//call_backoff=false;
//backoff2();
//cout<<"called backoff"<<endl;
////sleep(2);
//}
    }
}

void tactileCallback(const schunk_sdh::TactileSensor::ConstPtr& msg)
{


//    if(randi())
//        cout<<"tactilecalled  "<<" gripit = "<<gripit<<endl;

    //// Initialization.....
    for(int i = 0 ; i < 6 ; i++){Pstrong[i] = 0 ;}

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
//            cout<<sensorID<<"===="<<Pstrong[sensorID]<<endl;
//            cout<<(double)(ros::Time::now().toSec()-begin_t)<<endl;
//            cout<<begin_t<<endl;
        }

    }
    Pstrong[0]/=10;
    Pstrong[2]+=5;
    Pstrong[2]*=10;

    sensordata2.insert_cols(sensordata2.n_cols,1);
    rosTime2.insert_cols(rosTime2.n_cols,1);
    rosTime2(rosTime2.n_cols-1)=ros::Time::now().toSec()-begin_t;
    if(randi())
    {sensordata2.save("sensorc137",raw_ascii);
        rosTime2.save("rosTime2",raw_ascii);
    }

    double pmax=1000;

    if(grasp_type=="cube" && gripit && ((Pstrong[3]+Pstrong[5]>pmax)||((Pstrong[3]>pmax&&Pstrong[5]>pmax)))){
        gripit=false;
        call_backoff=true;
        mat saved_on_what_seq=zeros(1);
        saved_on_what_seq(0)=ros::Time::now().toSec()-begin_t;
        saved_on_what_seq.save("c137",raw_ascii);
        backoff2();
    }
  else  if( grasp_type=="sphere" && gripit &&(
                (Pstrong[1]>pmax&&  Pstrong[3]>pmax&&  Pstrong[5]>pmax)||
                (Pstrong[0]>pmax&&  Pstrong[2]>pmax&&  Pstrong[4]>pmax)
                )){
        gripit=false;
        call_backoff=true;
        mat saved_on_what_seq=zeros(1);
        saved_on_what_seq(0)=ros::Time::now().toSec()-begin_t;
        saved_on_what_seq.save("c137",raw_ascii);
        backoff2();
    }
  else  if( grasp_type=="cylinder" &&gripit && reachedproximal==false &&(

              Pstrong[0]>pmax/2&&  Pstrong[2]>pmax/2&&  Pstrong[4]>pmax/2  )){
        reachedproximal=true;

    }
   else if( grasp_type=="cylinder" &&gripit &&(
                Pstrong[1]>pmax &&  Pstrong[3]>pmax &&  Pstrong[5]>pmax
            /*&&  Pstrong[0]>10&&  Pstrong[2]>10&&  Pstrong[4]>10 */ )){
        gripit=false;cout<<"gripit=false"<<endl;
        call_backoff=true;
        mat saved_on_what_seq=zeros(1);
        saved_on_what_seq(0)=ros::Time::now().toSec()-begin_t;
        saved_on_what_seq.save("c137",raw_ascii);
          backoff2();
    }
//    if(gripit && Pstrong[0]+Pstrong[2]+Pstrong[4]>30){
//        reachedproximal=true;
//    }else reachedproximal=false;

    if(!openhand)  domainloop();

//    if(did_backoff){
//        did_backoff=false;

//        int P;
//        if(grasp_type=="sphere")
//{P=2000;}else if(grasp_type=="cylinder"){P=1600;}else{P=1500;}

//        if(!openhand) if(Pstrong[0]>P||Pstrong[2]>P||Pstrong[4]>P||Pstrong[1]>P||Pstrong[3]>P||Pstrong[5]>P)
//        {
//            call_backoff=true;
//cout<<"call_backoff=true"<<endl;

//        }else{            cout<<"call_backoff=false"<<endl;

//            for(int sensorID=0; sensorID < 6; sensorID++)
//{
//                        cout<<sensorID<<"===="<<Pstrong[sensorID]<<endl;


//            }
//        }
//    }



}




void backoff(const sdh_grasp::pre_grasp_pos_data& msg){
    cout<<"gotbackoff"<<endl;

    backoff2();
}
void grasp_type_callback(const sdh_grasp::grasp_info& msg) {
//    ros::NodeHandle nn;
//    std_srvs::Trigger trigger ;
    int counter88=0;
    while(!recover.call(trigger) && (counter88<3)){
        counter88++;
        ROS_WARN("Failed to call service driver/recover");
   usleep(1000000)     ;
   init.call(trigger);

       }
    if(counter88<3)
       ROS_INFO("driver recovered");
else
        ROS_INFO("driver recovery gave up");


    setvelocitymode();
    gripit=true;
    openhand=false;reachedproximal=false;
    //    reachedproximal=false;
    if(msg.type=="cylinder")justproximal=false;
    grasp_type=msg.type;
    //            feedback.data =1;
    //            set_feedback.publish(feedback);


}
void stop_callback(const sdh_grasp::grasp_info& msg) {
    setvelocitymode();
    gripit=false;
    openhand=false;reachedproximal=false;
    //    reachedproximal=false;
    if(msg.type=="cylinder")justproximal=false;
    grasp_type=msg.type;
    cout<<"got the stop it message"<<endl;

    //            feedback.data =1;
    //            set_feedback.publish(feedback);
    mat saved_on_what_seq=zeros(1);
    saved_on_what_seq(0)=ros::Time::now().toSec()-begin_t;
    saved_on_what_seq.save("c137",raw_ascii);

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

