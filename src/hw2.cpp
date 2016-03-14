#include "ros/ros.h"
#include "std_msgs/String.h" 
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
void poseCallback(const turtlesim::PoseConstPtr& msg){
	ROS_INFO("x: %.2f, y: %.2f", msg->x, msg->y);
}

void moveForward(ros::Publisher& out, geometry_msgs::Twist& msg, ros::Rate& rate){
	int count =0; //number of updates
    while(ros::ok()){
		out.publish(msg);		
    	rate.sleep();
		count++;
		if (count == 10) break; //after a second break
    }
}

void turn(ros::Publisher& out, geometry_msgs::Twist& msg, ros::Rate& rate){
	int count = 0;
	while(ros::ok()){
		count++;
    	out.publish(msg);
		rate.sleep();
		if (count == 40)break; //after 45 updates break
	}	
}	

int main(int argc, char **argv){
    const double SPEED_MPS = 0.328; //foot conversion
    ros::init(argc, argv, "move_turtle"); //init the ros packages
    ros::NodeHandle node; //node
    ros::Publisher outputPub = node.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10); //select the advertise node
	ros::Subscriber inputSub = node.subscribe("turtle1/pose", 10, poseCallback);
    geometry_msgs::Twist msg; //create the twist controler
    msg.linear.x = SPEED_MPS; //set the speed to be 1 ftps
    ros::Rate rate(10); //hrz of the updates 10 hrz
	while(ros::ok()){
		msg.linear.x = SPEED_MPS;
		moveForward(outputPub, msg, rate);	
		msg.linear.x = 0;
		msg.angular.z = -.4;
		turn(outputPub, msg, rate);
		msg.angular.z = 0;
	}
}
