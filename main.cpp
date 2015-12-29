#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>


void scanCallback (const sensor_msgs::LaserScan::ConstPtr& scan_msg)
 {
 geometry_msgs::Twist vel; //Declaration of the global variable

 ros::NodeHandle n;
 ros::Publisher vel_pub_=n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
 ros::Rate loop_rate(50);// The frequency of the loop
 ros::Time now;


    for (unsigned int x=0;x< scan_msg->ranges.size();x++){


             if(scan_msg->ranges[x]>=0.8) {

                vel.linear.x = 0.3;//forward speed
                vel.angular.z = 0.0;//rotation speed
                vel_pub_.publish(vel);

                }


              now = ros::Time::now();
              if(scan_msg->ranges[x]<=0.7){

                 while (ros::Time::now() < (now + ros::Duration(0.5))){

                    vel.linear.x = 0.05;//forward speed
                    vel.angular.z = 0.0;//rotation speed
                    vel_pub_.publish(vel);
                    loop_rate.sleep();

}
               }

               now = ros::Time::now();
               if(scan_msg->ranges[x]<= 0.6){

                    while (ros::Time::now() < (now + ros::Duration(0.5))){
                    vel.linear.x = 0.0;//forward speed
                    vel.angular.z = 0.0;//rotation speed
                    vel_pub_.publish(vel);}
                    loop_rate.sleep();

                }


     }
 }
int main(int argc, char** argv){
  ros::init(argc, argv, "DistanceObstacle");

  ros::NodeHandle n;
  ros::Publisher vel_pub_=n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  ros::Subscriber scan_sub = n.subscribe("scan", 1, scanCallback);

  ros::spin(); //Maintains subscription topic until "Ctrl + C" is received
  return 0;

}
