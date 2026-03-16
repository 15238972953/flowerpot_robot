#include "ros_interface.h"

RosInterface::RosInterface()
{
    latitude = 0;
    longitude = 0;
    yaw = 0;

    gps_sub = nh.subscribe("/gps/fix", 10, &RosInterface::gpsCallback, this);
    yaw_sub = nh.subscribe("/yaw_angle", 10, &RosInterface::yawCallback, this);

    start_pub = nh.advertise<std_msgs::String>("/robot_start", 10);
    spacing_pub = nh.advertise<std_msgs::Float32>("/robot/pot_spacing",10);
    layout_pub = nh.advertise<std_msgs::String>("/robot/pot_layout",10);
}

void RosInterface::gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg)
{
    latitude = msg->latitude;
    longitude = msg->longitude;
}

void RosInterface::yawCallback(const std_msgs::Float32::ConstPtr& msg)
{
    yaw = msg->data;
}

void RosInterface::spinOnce()
{
    ros::spinOnce();
}

void RosInterface::publishStart(bool start)
{
    std_msgs::String msg;

    if(start)
        msg.data = "START";
    else
        msg.data = "STOP";

    start_pub.publish(msg);
}

void RosInterface::publishPotSpacing(float spacing)
{
    std_msgs::Float32 msg;
    msg.data = spacing;
    spacing_pub.publish(msg);
}

void RosInterface::publishPotLayout(const std::string &layout)
{
    std_msgs::String msg;
    msg.data = layout;
    layout_pub.publish(msg);
}