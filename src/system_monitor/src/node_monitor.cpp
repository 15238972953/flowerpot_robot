#include "node_monitor.h"
#include <ros/master.h>
#include <iostream>

NodeMonitor::NodeMonitor() : all_ready_(false) {
    // 需要监控的节点列表
    required_nodes_.push_back("camera_node");  // 发布相机话题
    required_nodes_.push_back("imu_node");     // 发布IMU数据（包括偏航角）
    required_nodes_.push_back("yolo11_node");    // 发布YOLOv11检测结果（花盆坐标）
    required_nodes_.push_back("gps_node");     // 发布GPS数据（经纬度）
    required_nodes_.push_back("serial_stm32_node");   // 发布与STM32通信的信息
    required_nodes_.push_back("decision_making_node");   // 发布决策结果
    required_nodes_.push_back("potbot_hmi_node");   // 发布HMI界面
    required_nodes_.push_back("processdata_node");   // 发布多传感器处理结果
    required_nodes_.push_back("PointCloudFitting_node");   // 发布雷达点云拟合结果

    // 发布者
    ready_pub_ = nh_.advertise<std_msgs::Bool>("/system_ready", 10);
    
    // 定时器，每2秒检查一次
    check_timer_ = nh_.createTimer(ros::Duration(2.0), &NodeMonitor::checkNodes, this);
    
    ROS_INFO("Node monitor started, monitoring %d nodes", (int)required_nodes_.size());
}

NodeMonitor::~NodeMonitor() {
}

bool NodeMonitor::isNodeRunning(const std::string& node_name) {
    // 获取所有运行中的节点
    std::vector<std::string> nodes;
    if (ros::master::getNodes(nodes)) {
        for (const auto& node : nodes) {
            // 直接匹配节点名
            if (node == node_name || 
                node.find(node_name) != std::string::npos) {
                return true;
            }
        }
    }
    return false;
}

void NodeMonitor::checkNodes(const ros::TimerEvent& event) {
    bool all_ready = true;
    std::vector<std::string> missing_nodes;
    
    // 检查每个节点是否运行
    for (const auto& node : required_nodes_) {
        if (!isNodeRunning(node)) {
            all_ready = false;
            missing_nodes.push_back(node);
        }
    }
    
    // 状态变化时打印信息
    if (all_ready && !all_ready_) {
        ROS_INFO("All nodes are ready!");
    } else if (!all_ready && all_ready_) {
        ROS_WARN("System disconnected, some nodes are offline");
    } else if (!all_ready) {
        // 每10秒打印一次等待信息
        static int count = 0;
        if (++count >= 5) {
            count = 0;
            ROS_INFO("Waiting for nodes: %d/%d", 
                     (int)(required_nodes_.size() - missing_nodes.size()),
                     (int)required_nodes_.size());
            for(const auto& node_ : missing_nodes){
                ROS_ERROR("missing_node:%s", node_.c_str());
            }
        }
    }
    
    all_ready_ = all_ready;
    
    // 发布状态
    std_msgs::Bool msg;
    msg.data = all_ready_;
    ready_pub_.publish(msg);
}

void NodeMonitor::run() {
    ros::spin();
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "node_monitor");
    
    NodeMonitor monitor;
    monitor.run();
    
    return 0;
}