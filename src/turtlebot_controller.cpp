#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"
#include <stdlib.h>
#include <sstream>

double no_ball_threshold= 0.01;
geometry_msgs::Twist vel;
ros::Publisher controller;

void listenerCallback(const geometry_msgs::Point::ConstPtr& msg){
	ROS_INFO("Position x: %f, y: %f", msg->x, msg->y);
	// if x and y are below 0.1, no ball deteced. Stay. 
	// if ball deteced, spin a circle;
	//if( (abs(msg->x) <= no_ball_threshold) && (abs(msg->y) <= no_ball_threshold) ){
	if( msg->x == 0 && msg->y == 0){
		vel.linear.x = 0;
		vel.angular.z = 0;
		
	}else{
		vel.linear.x = 0.1;
		vel.angular.z = 0.1;
	}
	controller.publish(vel);
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtlebot_controller");
	ros::NodeHandle n;
	controller = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    ros::Subscriber listener = n.subscribe("/obj_pos", 1000, listenerCallback);

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
      ros::spinOnce();

      loop_rate.sleep();
    }

  return 0;
}
