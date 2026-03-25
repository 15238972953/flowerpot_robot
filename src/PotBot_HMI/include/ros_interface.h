#ifndef ROS_INTERFACE_H
#define ROS_INTERFACE_H

#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include <decision_making_pkg/StartTransport.h>

class RosInterface
{
public:
    RosInterface();
    ~RosInterface();

    double latitude;
    double longitude;
    float yaw;
    int transported_pot_count; // 已搬运花盆数量
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
    ros::Subscriber transported_pot_count_sub;
    // Service Client
    ros::ServiceClient client_;
    
    bool service_ready_;
    
    // ros::Publisher start_pub;
    // ros::Publisher spacing_pub;
    // ros::Publisher layout_pub;
private:
    void gpsCallback(const std_msgs::Float64MultiArray::ConstPtr& msg);
    void yawCallback(const std_msgs::Float32::ConstPtr& msg);
    void transportedPotCountCallback(const std_msgs::Int8::ConstPtr& msg);
};

#endif