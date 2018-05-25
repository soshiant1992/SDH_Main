#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Bool.h>

#include "string.h"
#include "sensor_msgs/JointState.h"

#include <schunk_sdh/TactileSensor.h>
#include <schunk_sdh/TactileMatrix.h>
#include "std_srvs/Trigger.h"


#include <tf/transform_listener.h>
#include <eigen3/Eigen/Dense>
#include <tf/LinearMath/Matrix3x3.h>

#include <sdh_grasp/spatial_array.h>


using namespace Eigen;

int sensorID;
int tactile_flag;

void convert_coor(tf::StampedTransform &transform, const tf::TransformListener &listener, const std::string s1, const std::string s2, int i);

ros::ServiceClient client;
ros::Subscriber sub;
float coor[6][4];


void tactileCallback(const schunk_sdh::TactileSensor::ConstPtr& msg)
{
     int sum = 0;
     float y_coor=0;
     float x_coor=0;
     int max  = 0 ;

     int sz = msg->tactile_matrix[sensorID].cells_x * msg->tactile_matrix[sensorID].cells_y ;

     for (int i = 0; i < sz; i++)
     {
         int val = msg->tactile_matrix[sensorID].tactile_array[i];
         sum= sum + val;

         x_coor += val*((i+1+msg->tactile_matrix[sensorID].cells_y)/msg->tactile_matrix[sensorID].cells_y);
         y_coor += val*((i+1+msg->tactile_matrix[sensorID].cells_x)/msg->tactile_matrix[sensorID].cells_x);

         if(max < val)
         {
            max  = val;
         }
     }

        if(max != 0)
        {
           coor[sensorID][0] = 1;
           if(sensorID < 2)
           {
            coor[sensorID][2] = 0.0034*(float(x_coor/sum)- 3);
           }
           else
           coor[sensorID][2] = 0.0034*(3- float(x_coor/sum));
           coor[sensorID][3] = 0.02 +  0.0034*(msg->tactile_matrix[sensorID].cells_y- (y_coor/sum));
        }
        else
        {
            coor[sensorID][0] = 0;
            coor[sensorID][1] = 0;
            coor[sensorID][2] = 0;
        }

        coor[0][1] = 0.0125;
        coor[1][1] = 0.0125;
        coor[2][1] = -0.0125;
        coor[3][1] = -0.0125;
        coor[4][1] = -0.0125;
        coor[5][1] = -0.0125;

       /* ROS_INFO("x_coor =%f",x_coor);
         ROS_INFO("sum =%d",sum);
        ROS_INFO("coor_check[0][0] =%f",coor[0][0]);
        ROS_INFO("coor_check[0][1] =%f",coor[0][1]);
        ROS_INFO("coor_check[0][2] =%f",coor[0][2]);
        ROS_INFO("coor_check[0][3] =%f",coor[0][3]);*/

        y_coor =0;
        x_coor =0;
        sum =0;
    // std::cout<<"loop"<<std::endl;
     tactile_flag =1;
     sensorID = sensorID + 1 ;

}



void convert_coor(tf::StampedTransform &transform, const tf::TransformListener &listener, const std::string s1, const std::string s2, int i)
{
             try{
               ros::Time now = ros::Time::now();
                 listener.waitForTransform(s1,s2,
                                           now, ros::Duration(1.0));
                 listener.lookupTransform(s1,s2,
                                          now, transform);
             }
             catch (tf::TransformException ex){
                 ROS_INFO("error in conver coor");

              // ROS_ERROR("%s",ex.what());
              // ros::Duration(1.0).sleep();
             }



   MatrixXd m(3,3);

   tf::Matrix3x3 mat = transform.getBasis();

   tf::Vector3 vec1 = mat.getRow(0);
   tf::Vector3 vec2 = mat.getRow(1);
   tf::Vector3 vec3 = mat.getRow(2);

   m(0,0) = vec1.x();
   m(0,1) = vec1.y();
   m(0,2) = vec1.z();
   m(1,0) = vec2.x();
   m(1,1) = vec2.y();
   m(1,2) = vec2.z();
   m(2,0) = vec3.x();
   m(2,1) = vec3.y();
   m(2,2) = vec3.z();

   VectorXd v(3);
   v << coor[i][1] , coor[i][2],coor[i][3];

   if(transform.getOrigin().z() >0.001 | transform.getOrigin().z() <-0.001 |transform.getOrigin().x() >0.001 | transform.getOrigin().x() <-0.001 |transform.getOrigin().y() >0.001 | transform.getOrigin().y() <-0.001 )
   {
       ROS_INFO("inside if");

   MatrixXd result (3,1);

  // std::cout <<"m"<<m <<std::endl;
  // std::cout <<"v"<<v<<std::endl;
   result = m*v;
  // std::cout <<"m*v"<<result <<std::endl;

   result(0,0) += transform.getOrigin().x();
   result(1,0) += transform.getOrigin().y();
   result(2,0) += transform.getOrigin().z();

  // std::cout <<"result"<<result <<std::endl;

   coor[i][1] = result(0,0);
   coor[i][2] = result(1,0);
   coor[i][3] = result(2,0) ;

  }
   else
      {
       convert_coor(transform, listener,s1,s2,i);
      }
}

void  calculate_coor(tf::StampedTransform &transform, const tf::TransformListener &listener )
{
    ROS_INFO("checking");
    if(coor[0][0]==1)
    {

        std::string s1 ("/sdh_thumb_1_link");
        std::string s2 ("/sdh_thumb_2_link");
        convert_coor(transform, listener,s1,s2,0);
        ROS_INFO("halfdone");

        std::string s11 ("/sdh_palm_link");
        std::string s22 ("/sdh_thumb_1_link");
        convert_coor(transform, listener,s11,s22,0);
        ROS_INFO("fulldone");

        ROS_INFO("coor[0][0] =%f",coor[0][0]);
        ROS_INFO("coor[0][1] =%f",coor[0][1]);
        ROS_INFO("coor[0][2] =%f",coor[0][2]);
        ROS_INFO("coor[0][3] =%f",coor[0][3]);
    }
    if(coor[2][0]==1)
    {

        std::string s1 ("/sdh_finger_11_link");
        std::string s2 ("/sdh_finger_12_link");
        convert_coor(transform, listener,s1,s2,2);
        ROS_INFO("halfdone");

        std::string s11 ("/sdh_palm_link");
        std::string s22 ("/sdh_finger_11_link");
        convert_coor(transform, listener,s11,s22,2);
        ROS_INFO("fulldone");

        ROS_INFO("coor[2][0] =%f",coor[2][0]);
        ROS_INFO("coor[2][1] =%f",coor[2][1]);
        ROS_INFO("coor[2][2] =%f",coor[2][2]);
        ROS_INFO("coor[2][3] =%f",coor[2][3]);
    }
    if(coor[4][0]==1)
    {

        std::string s1 ("/sdh_finger_21_link");
        std::string s2 ("/sdh_finger_22_link");
        convert_coor(transform, listener,s1,s2,4);
        ROS_INFO("halfdone");

        std::string s11 ("/sdh_palm_link");
        std::string s22 ("/sdh_finger_21_link");
        convert_coor(transform, listener,s11,s22,4);
        ROS_INFO("fulldone");

        ROS_INFO("coor[4][0] =%f",coor[4][0]);
        ROS_INFO("coor[4][1] =%f",coor[4][1]);
        ROS_INFO("coor[4][2] =%f",coor[4][2]);
        ROS_INFO("coor[4][3] =%f",coor[4][3]);
    }


    if(coor[1][0]==1)
        {

            std::string s1 ("/sdh_thumb_2_link");
            std::string s2 ("/sdh_thumb_3_link");
            convert_coor(transform, listener,s1,s2,1);
            ROS_INFO("one third done");

            std::string s11 ("/sdh_thumb_1_link");
            std::string s22 ("/sdh_thumb_2_link");
            convert_coor(transform, listener,s11,s22,1);
            ROS_INFO("two third done");

            std::string s111 ("/sdh_palm_link");
            std::string s222 ("/sdh_thumb_1_link");
            convert_coor(transform, listener,s111,s222,1);
            ROS_INFO("fulldone");

            ROS_INFO("coor[1][0] =%f",coor[1][0]);
            ROS_INFO("coor[1][1] =%f",coor[1][1]);
            ROS_INFO("coor[1][2] =%f",coor[1][2]);
            ROS_INFO("coor[1][3] =%f",coor[1][3]);
        }

      if(coor[3][0]==1)
        {

            std::string s1 ("/sdh_finger_12_link");
            std::string s2 ("/sdh_finger_13_link");
            convert_coor(transform, listener,s1,s2,3);
            ROS_INFO("one third done");

            std::string s11 ("/sdh_finger_11_link");
            std::string s22 ("/sdh_finger_12_link");
            convert_coor(transform, listener,s11,s22,3);
            ROS_INFO("two third done");

            std::string s111 ("/sdh_palm_link");
            std::string s222 ("/sdh_finger_11_link");
            convert_coor(transform, listener,s111,s222,3);
            ROS_INFO("fulldone");

            ROS_INFO("coor[3][0] =%f",coor[3][0]);
            ROS_INFO("coor[3][1] =%f",coor[3][1]);
            ROS_INFO("coor[3][2] =%f",coor[3][2]);
            ROS_INFO("coor[3][3] =%f",coor[3][3]);
        }
      if(coor[5][0]==1)
        {

            std::string s1 ("/sdh_finger_22_link");
            std::string s2 ("/sdh_finger_23_link");
            convert_coor(transform, listener,s1,s2,5);
            ROS_INFO("one third done");

            std::string s11 ("/sdh_finger_21_link");
            std::string s22 ("/sdh_finger_22_link");
            convert_coor(transform, listener,s11,s22,5);
            ROS_INFO("two third done");

            std::string s111 ("/sdh_palm_link");
            std::string s222 ("/sdh_finger_21_link");
            convert_coor(transform, listener,s111,s222,5);
            ROS_INFO("fulldone");

            ROS_INFO("coor[5][0] =%f",coor[5][0]);
            ROS_INFO("coor[5][1] =%f",coor[5][1]);
            ROS_INFO("coor[5][2] =%f",coor[5][2]);
            ROS_INFO("coor[5][3] =%f",coor[5][3]);
        }
}





int main(int argc, char **argv)
{

    bool trigger = true;
    float sl_time = 1;

    ros::init(argc, argv, "spatial");

    ros::NodeHandle n;
    tf::TransformListener listener;
    tf::StampedTransform transform;

    ros::ServiceClient client = n.serviceClient<std_srvs::Trigger>("/driver/init");
    std_srvs::Trigger srv;

    if (client.call(srv))
    {
    }
      else
    {
        ROS_ERROR("Failed to call service driver/init");
        return 1;
    }

    sub = n.subscribe("/dsa_controller/tactile_data", 2, tactileCallback);
    ros::Publisher poseArrayPub =  n.advertise<sdh_grasp::spatial_array> ("/spatial", 6);

    ros::NodeHandle v ("~");

            v.getParam("trigger",trigger);
            v.getParam("frequency",sl_time);


    while(ros::ok())
    {
        while(trigger)
        {
            sensorID = 0;

            tactile_flag =0;
            while(sensorID <6)
            {
                ros::spinOnce();
            }
            ros::spinOnce();


            ROS_INFO("coor[0][0] =%f",coor[0][0]);
            ROS_INFO("coor[1][0] =%f",coor[1][0]);
            ROS_INFO("coor[2][0] =%f",coor[2][0]);
            ROS_INFO("coor[3][0] =%f",coor[3][0]);
            ROS_INFO("coor[4][0] =%f",coor[4][0]);
            ROS_INFO("coor[5][0] =%f",coor[5][0]);

            calculate_coor(transform, listener);



            sdh_grasp::spatial_array abc;

            for( int i =1; i<7 ; i++)
            {
                abc.type ="tactile_sensor" + boost::lexical_cast<std::string>(i-1);
                if(coor[i-1][0] == 1)
                {
                    abc.x = coor[i-1][1];
                    abc.y = coor[i-1][2];
                    abc.z = coor[i-1][3];
                }
                else
                {
                    abc.x = 0;
                    abc.y = 0;
                    abc.z = 0;
                }

                poseArrayPub.publish(abc);

            }

            ros::Duration(1/sl_time).sleep();

        }

    }
    return 0;
}
