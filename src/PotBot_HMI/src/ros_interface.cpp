#include "ros_interface.h"

RosInterface::RosInterface():service_ready_(false)
{
    latitude = 0;
    longitude = 0;
    yaw = 0;

    gps_sub = nh.subscribe("gps_data", 10, &RosInterface::gpsCallback, this);
    yaw_sub = nh.subscribe("/yaw_angle", 10, &RosInterface::yawCallback, this);

    // start_pub = nh.advertise<std_msgs::String>("/robot_start", 10);
    // spacing_pub = nh.advertise<std_msgs::Float32>("/robot/pot_spacing",10);
    // layout_pub = nh.advertise<std_msgs::String>("/robot/pot_layout",10);

    // 创建Service客户端
    client_ = nh_.serviceClient<decision_making_pkg::StartTransport>("/start_transport");
    
    // 检查Service是否可用
    checkService();
}

~RosInterface::~RosInterface() {}

bool RosInterface::checkService() {
    service_ready_ = client_.exists();
    if (service_ready_) {
        ROS_INFO("Service /start_transport 已连接");
    } else {
        ROS_WARN("Service /start_transport 不可用，请确保决策节点已启动");
    }
    return service_ready_;
}

bool RosInterface::sendTransportTask(int placement_type, float placement_spacing, bool start) {
    // 如果Service不可用，重新检查一次
    if (!service_ready_) {
        checkService();
        if (!service_ready_) {
            ROS_ERROR("Service不可用，无法发送指令");
            return false;
        }
    }
    
    // 创建请求
    decision_making_pkg::StartTransport srv;
    srv.request.placement_type = placement_type;
    srv.request.placement_spacing = placement_spacing;
    srv.request.start = start;
    
    // 发送请求
    if (client_.call(srv)) {
        if (srv.response.success) {
            ROS_INFO("指令发送成功: %s", srv.response.message.c_str());
            return true;
        } else {
            ROS_ERROR("指令发送失败: %s", srv.response.message.c_str());
            return false;
        }
    } else {
        ROS_ERROR("Service调用失败");
        service_ready_ = false;  // 标记为不可用，下次重新检查
        return false;
    }
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

// void RosInterface::publishStart(bool start)
// {
//     std_msgs::String msg;

//     if(start)
//         msg.data = "START";
//     else
//         msg.data = "STOP";

//     start_pub.publish(msg);
// }

// void RosInterface::publishPotSpacing(float spacing)
// {
//     std_msgs::Float32 msg;
//     msg.data = spacing;
//     spacing_pub.publish(msg);
// }

// void RosInterface::publishPotLayout(const std::string &layout)
// {
//     std_msgs::String msg;
//     msg.data = layout;
//     layout_pub.publish(msg);
// }

