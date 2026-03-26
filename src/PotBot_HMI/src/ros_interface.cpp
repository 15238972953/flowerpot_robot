#include "ros_interface.h"

RosInterface::RosInterface() : service_ready_(false)
{
    latitude = 0;
    longitude = 0;
    yaw = 0;
    
    // 订阅GPS和Yaw数据
    gps_sub = nh.subscribe("gps_data", 10, &RosInterface::gpsCallback, this);
    yaw_sub = nh.subscribe("/yaw_angle", 10, &RosInterface::yawCallback, this);
    transported_pot_count_sub = nh.subscribe("/transported_pot_count", 10, &RosInterface::transportedPotCountCallback, this);
    ready_sub_ = nh.subscribe("/system_ready", 10, &RosInterface::readyCallback, this);
    
    // 如果需要发布者，取消注释
    // start_pub = nh.advertise<std_msgs::String>("/robot_start", 10);
    // spacing_pub = nh.advertise<std_msgs::Float32>("/robot/pot_spacing", 10);
    // layout_pub = nh.advertise<std_msgs::String>("/robot/pot_layout", 10);
    
    // 等待服务可用
    if(!ros::service::waitForService("/start_transport", ros::Duration(5.0)))
    {
        ROS_ERROR("Service /start_transport 不可用，请确保决策节点已启动");
        service_ready_ = false;
    }
    else
    {
        // 创建Service客户端
        client_ = nh.serviceClient<decision_making_pkg::StartTransport>("/start_transport");
        
        // 检查Service是否可用
        checkService();
    }
}

RosInterface::~RosInterface()
{
    ROS_INFO("RosInterface destroyed");
}

bool RosInterface::checkService() {
    // 如果客户端未创建，尝试创建
    if (!client_) {
        if (ros::service::exists("/start_transport", false)) {
            client_ = nh.serviceClient<decision_making_pkg::StartTransport>("/start_transport");
        } else {
            service_ready_ = false;
            ROS_WARN("Service /start_transport 不存在");
            return false;
        }
    }
    
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
        ROS_WARN("Service未就绪，尝试重新连接...");
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
    
    // 打印发送的信息
    ROS_INFO("发送运输任务: placement_type=%d, placement_spacing=%.2f, start=%s", 
             placement_type, placement_spacing, start ? "true" : "false");
    
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
        ROS_ERROR("Service调用失败，请检查决策节点是否运行");
        service_ready_ = false;  // 标记为不可用，下次重新检查
        return false;
    }
}


void RosInterface::gpsCallback(const std_msgs::Float64MultiArray::ConstPtr& msg)
{
    latitude = msg->data[0];
    longitude = msg->data[1];
}

void RosInterface::yawCallback(const std_msgs::Float32::ConstPtr& msg)
{
    yaw = msg->data;
}

void RosInterface::transportedPotCountCallback(const std_msgs::Int8::ConstPtr& msg)
{
    transported_pot_count = msg->data;
    ROS_INFO("已搬运花盆数量更新: %d", transported_pot_count);
}

void RosInterface::readyCallback(const std_msgs::Bool::ConstPtr& msg)
{
    system_ready_ = msg->data;
    ROS_INFO("系统准备状态更新: %s", system_ready_ ? "已就绪" : "未就绪");
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

