#include<ros/ros.h>
#include<std_msgs/Float32.h>
#include<geometry_msgs/Twist.h>

ros::Publisher twist_pub;
geometry_msgs::Twist robotspeed;

void sonarCallback(const std_msgs::Float32ConstPtr &msg){
    
    ROS_INFO("Received message, %f", msg->data);
    
    if ( msg->data!=0)
    {
        robotspeed.linear.x = 0;
        robotspeed.angular.z = 0;
    }
    else
    {
        robotspeed.linear.x = 1;
        robotspeed.angular.z = 0;
    }
    twist_pub.publish(robotspeed);
}

int main(int argc, char **argv){
    
    ros::init(argc, argv, "simple_avoidance");
    ros::NodeHandle nh;
    twist_pub = nh.advertise<geometry_msgs::Twist>("obstacle/Twist",1);
    ros::Subscriber sonar_sub = nh.subscribe("/vrep/vehicle/frontSonar", 1, sonarCallback);
    ros::spin();
    
}