#ifndef ROS_INTERFACE_H
#define ROS_INTERFACE_H

#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include "decision_making_pkg/StartTransport.h"

class RosInterface
{
public:
    RosInterface();
    ~RosInterface();

    void spinOnce();

    double latitude;
    double longitude;
    float yaw;
public:
    // void publishStart(bool start);
    // void publishPotSpacing(float spacing);
    // void publishPotLayout(const std::string &layout);

    // 发送运输任务配置（摆放方式、摆放间距、开始标志）
    bool sendTransportTask(int placement_type, float placement_spacing, bool start);
    // 检查Service是否可用
    bool checkService();
private:
    ros::NodeHandle nh;

    ros::Subscriber gps_sub;
    ros::Subscriber yaw_sub;
    // Service Client
    ros::ServiceClient start_transport_client_;
    
    bool service_ready_;
    
    // ros::Publisher start_pub;
    // ros::Publisher spacing_pub;
    // ros::Publisher layout_pub;
private:
    ros::service::waitForService("/start_transport", ros::Duration(5.0));
    void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg);
    void yawCallback(const std_msgs::Float32::ConstPtr& msg);
};

#endif