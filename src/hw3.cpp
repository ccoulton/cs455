#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
int main (int argc, char **argv){
    ros::init(argc, argv, "move_create");
    ros::NodeHandle node;
    ros::Publisher cmd_vel_topic = node.advertise<geometry_msgs::Twist>("cmd_vel",1000);
	//ros::Subcriber inputSub = node.subscribe("create/pose", 10,);
    ros::Rate loopHrz(10);
    int count=0;
    while(ros::ok()){
        geometry_msgs::Twist twist;
        twist.linear.x = 1;
        twist.linear.y = 0;
        twist.linear.z = 0;
        cmd_vel_topic.publish(twist);
        loopHrz.sleep();
        ++count;
    }
    return 0;
}
