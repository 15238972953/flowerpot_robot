// dubins_path_planner.cpp
#include "dubins_path_planner.h"
#include <cmath>
#include <iostream>

DubinsPathPlanner::DubinsPathPlanner() : nh_(""), pnh_("~"),
    current_PosePoint_(0, 0, 0), target_point_(0, 0), next_Point_(0, 0),
    step_distance_(0.2), arrival_threshold_(0.1)
{
    // 获取参数
    pnh_.param<double>("step_distance", step_distance_, 0.2);      // 每步0.2米
    pnh_.param<double>("arrival_threshold", arrival_threshold_, 0.1); // 到达阈值0.1米
    
    // 订阅GPS数据（格式: [纬度, 经度, 质量, 卫星数]）
    gps_sub_ = nh_.subscribe("/gps_data", 10, &DubinsPathPlanner::gpsCallback, this);
    
    // 订阅偏航角（从IMU获取）
    yaw_sub_ = nh_.subscribe("/yaw_angle", 10, &DubinsPathPlanner::yawCallback, this);
    
    // 订阅目标花盆坐标
    target_sub_ = nh_.subscribe("/target_position", 1, &DubinsPathPlanner::targetCallback, this);
    
    // 发布下一个目标点
    next_target_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/next_position", 10);
    
    ROS_INFO("Dubins路径规划节点初始化完成");
    ROS_INFO("  步长距离: %.2f 米", step_distance_);
    ROS_INFO("  到达阈值: %.2f 米", arrival_threshold_);
}

DubinsPathPlanner::~DubinsPathPlanner() {}

// 处理接收到的GPS数据
void DubinsPathPlanner::gpsCallback(const std_msgs::Float64MultiArray::ConstPtr& msg) {
    if (msg->data.size() < 2) return;
    
    double lat = msg->data[0];
    double lon = msg->data[1];
    int quality = (int)msg->data[2];
    
    if (quality > 3) {
        if (!ref_initialized) {   // 只接收GPS数据中的第一个有效点作为参考点
            ref_lat_ = lat;
            ref_lon_ = lon;
            ref_initialized = true;
            ROS_INFO("参考点已设置: (%.8f, %.8f)", ref_lat_, ref_lon_);
        }else {
            current_PosePoint_.point = latLonToXY(lat, lon, ref_lat_, ref_lon_);
        }
        ROS_DEBUG("GPS更新: (%.8f, %.8f) -> (%.3f, %.3f)", lat, lon, current_PosePoint_.point.x, current_PosePoint_.point.y);
    } 
}

// 处理接收到的yaw数据
void DubinsPathPlanner::yawCallback(const std_msgs::Float32::ConstPtr& yaw_msg) {
    current_PosePoint_.yaw = yaw_msg->data;
    ROS_DEBUG("航向角更新: %.2f°", current_PosePoint_.yaw);
}

// 处理接收到的目标花盆位置
void DubinsPathPlanner::targetCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
    // 接收目标花盆位置（假设在局部坐标系中）
    target_point_.x = msg->pose.position.x;
    target_point_.y = msg->pose.position.y;

    ROS_INFO("收到新目标: (%.3f, %.3f)", 
             target_point_.x, target_point_.y);
}

// 将经纬度转换为相对于参考点的平面坐标
Point2D DubinsPathPlanner::latLonToXY(double lat, double lon, double ref_lat, double ref_lon) {
    const double R = 6371000.0; // 地球半径（米）
    double lat_rad = lat * M_PI / 180.0;
    double lon_rad = lon * M_PI / 180.0;
    double ref_lat_rad = ref_lat * M_PI / 180.0;
    double ref_lon_rad = ref_lon * M_PI / 180.0;
    
    double x = R * (lon_rad - ref_lon_rad) * cos(ref_lat_rad);
    double y = R * (lat_rad - ref_lat_rad);
    
    return Point2D(x, y);
}

// 归一化角度到[-pi, pi]
double DubinsPathPlanner::normalizeAngle(double angle) {
    while (angle > M_PI) angle -= 2 * M_PI;
    while (angle < -M_PI) angle += 2 * M_PI;
    return angle;
}

// 计算两点之间的距离
double DubinsPathPlanner::distance(Point2D point1, Point2D point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

// 计算下一个目标点的坐标
void DubinsPathPlanner::calculateNextTargetPoint() {
    // 如果距离目标点大于步长距离，则设置下一个目标点为沿直线方向的步长距离点,否则直接设置为目标点
    if(distance(current_PosePoint_.point, target_point_) > step_distance_) {
        double dx = target_point_.x - current_PosePoint_.point.x;
        double dy = target_point_.y - current_PosePoint_.point.y;
        double dist_to_target = sqrt(dx * dx + dy * dy);
        next_Point_.x = current_PosePoint_.point.x + dx / dist_to_target * step_distance_;
        next_Point_.y = current_PosePoint_.point.y + dy / dist_to_target * step_distance_;
    }else {
        next_Point_ = target_point_;
    }

}

// 这里还有问题，待优化:2026.3.23（pengdefeng）
void DubinsPathPlanner::run() {
    ros::Rate rate(20); // 20Hz
    
    while (ros::ok()) {
        ros::spinOnce();

        // calculateNextTargetPoint();
        double dist_to_next = distance(current_PosePoint_.point, next_Point_);
        if(dist_to_next < arrival_threshold_) {
            // 检查是否到达当前目标点
            double dist_to_target = distance(current_PosePoint_.point, target_point_);
            if (dist_to_target < arrival_threshold_) {
                ROS_INFO("到达目标点 (%.3f, %.3f)", 
                        target_point_.x, target_point_.y);
            } else {
                ROS_INFO("到达当前目标点 (%.3f, %.3f)", next_Point_.x, next_Point_.y);
                calculateNextTargetPoint();
                next_target_pub_.publish(next_Point_);
            }
        }   
        rate.sleep();
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "path_planner_node");
    
    DubinsPathPlanner planner;
    planner.run();
    
    return 0;
}