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


int sensorID;
int tactile_flag;
int position_flag;
int cnt_ =0;
int axb =0;
int non_zero =0;
double dd_prev =0;
int slip_counting =0;

int hold_smooth =0;
int hold_hard =0;


ros::Publisher slip_pub_d;
ros::Publisher slip_pub_dd;

ros::ServiceClient client;

std::ofstream myfile;
std::ofstream myfile1;

void tactileCallback(const schunk_sdh::TactileSensor::ConstPtr& msg)
 {

    int flag_pub =0;

     std::string data("");
     int max  = 0 ;
     int sum = 0;
     int sz = msg->tactile_matrix[sensorID].cells_x * msg->tactile_matrix[sensorID].cells_y ;
     if(sensorID =4)
     {
     myfile << "Sensor id  = "<<sensorID;
     }

     for (int i = 0; i < sz; i++)
     {


         int val = msg->tactile_matrix[sensorID].tactile_array[i];

         if(sensorID =4 )
        {
            non_zero++;
            sum = sum +val;
        }
         if(max < val)
         {
            max  = val ;
         }
        std::ostringstream ss;
        ss << val;
        data.append(ss.str());
        data.append(", ");

        ss.flush();
     }
     cnt_++;
     myfile <<",";
     myfile << sum;
     myfile << "\n";
            //myfile << "\n";


            if(cnt_ = 50)
            {
                cnt_ = 0;
                int flag =1;
                myfile1 << double(sum/non_zero);
                myfile1 <<",";
                double ycz = sum - axb;
                ycz = ycz/50;
                double dd_curr = ycz-dd_prev;
                dd_prev = ycz;
                myfile1 << ycz;

                if(ycz >= 2 | ycz <= -2)
                {
                    if(ycz <= 8 | ycz >= -8)
                    {
                    flag =0;

                    myfile1 <<",";
                    myfile1 << "slip_d_smooth";
                    hold_smooth++;
                    }
                    if(ycz >= 8 | ycz <= -8)
                    {
                        flag =0;

                        myfile1 <<",";
                        myfile1 << "slip_d_hard";
                        hold_hard++;
                    }

                }


                if(dd_curr >= 3 | dd_curr <= -3)
                {
                    if(flag ==1)
                    {
                        myfile1 <<",";
                    }


                    slip_counting++;
                    myfile1 <<",";
                    myfile1 << "slip_dd";

                }
                if(slip_counting >=8)
                   { std_msgs::Bool status;
                    status.data =1;
                slip_pub_dd.publish(status);
                slip_counting =0;
                }
                if( hold_hard >3 && hold_smooth >5)
                {
                    std_msgs::Bool status;
                    status.data =0;
                    slip_pub_d.publish(status);
                    hold_hard =0;
                    hold_smooth=0;
                    flag_pub = 1;
                }
                if( hold_smooth >8)
                {
                    std_msgs::Bool status;
                    status.data =1;
                    if(flag_pub == 0)
                    //slip_pub_d.publish(status);
                    hold_smooth=0;

                }
                myfile1 << "\n";
                axb = sum;

            }
             sum = 0;

       // ROS_INFO("Tactile sensor: [%d]  max_value: [%d]", sensorID, max);

     sensorID = sensorID + 1 ;
     if(sensorID > 5)
     {
        sensorID = 0 ;        
     }
 }

int main(int argc, char **argv)
{
    //std::clock_t start;
    //double duration;
    //start = std::clock();
    sensorID = 0;

    myfile.open ("dat1.csv");
    myfile1.open ("data2.csv");

    ros::init(argc, argv, "slip_detect");

    ros::NodeHandle n;

    ros::ServiceClient client = n.serviceClient<std_srvs::Trigger>("/driver/init");
    std_srvs::Trigger srv ;

    if (client.call(srv))
    {
    }
      else
    {
     ROS_ERROR("Failed to call service driver/init");
     return 1;
    }

    ros::Subscriber sub2 = n.subscribe("/dsa_controller/tactile_data", 1000, tactileCallback);
    slip_pub_d = n.advertise<std_msgs::Bool>("/slip_detect_d", 10);
    slip_pub_dd = n.advertise<std_msgs::Bool>("/slip_detect_dd", 10);
    ros::spin();
    //duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    //std::cout<<"printf: "<< duration <<'\n';

    myfile.close();
    myfile1.close();
    return 0;
}
