#ifndef ROS_INTERFACE_H
#define ROS_INTERFACE_H

#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>

class RosInterface
{
public:
    RosInterface();

    void spinOnce();

    double latitude;
    double longitude;
    float yaw;

    void publishStart(bool start);
    void publishPotSpacing(float spacing);
    void publishPotLayout(const std::string &layout);

private:
    ros::NodeHandle nh;

    ros::Subscriber gps_sub;
    ros::Subscriber yaw_sub;

    ros::Publisher start_pub;
    ros::Publisher spacing_pub;
    ros::Publisher layout_pub;

    void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg);
    void yawCallback(const std_msgs::Float32::ConstPtr& msg);
};

#endif