// dubins_path_planner.h
#ifndef DUBINS_PATH_PLANNER_H
#define DUBINS_PATH_PLANNER_H

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Float64MultiArray.h>
#include <vector>
#include <cmath>

struct Point2D {
    double x, y;      // 转换后的平面坐标
    Point2D(double x_ = 0, double y_ = 0, double yaw_ = 0) : x(x_), y(y_), yaw(yaw_) {}
};

// 位姿点（包含位置和航向）
struct PosePoint
{
    Point2D point;
    double yaw;      // 航向角
    PosePoint(double x = 0, double y = 0, double yaw_ = 0) : point(x, y), yaw(yaw_) {}
};


class DubinsPathPlanner {
private:
    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
    
    // 订阅者
    ros::Subscriber gps_sub_;
    ros::Subscriber yaw_sub_;
    ros::Subscriber target_sub_;   // 目标点坐标订阅者
    
    // 发布者 - 发布下一个目标点
    ros::Publisher next_target_pub_;    //机器人规划出来的下一个轨迹点
    
    // 当前状态
    PosePoint current_PosePoint_;              // 当前位姿
    
    // 目标状态

    Point2D target_point_;               // 目标位置
    
    // 临时目标点（当前要去的点）
    Point2D next_Point_;                 // 当前要去的点

        
    // 路径规划参数
    double step_distance_;               // 每步距离（米）
    double arrival_threshold_;           // 设定是否到达阈值（米）

    static bool ref_initialized;     // 是否已初始化参考点,以机器人上电点为参考点，将其他GPS坐标转换为相对于该点的平面坐标
    static double ref_lat_;
    static double ref_lon_;

public:
    DubinsPathPlanner();
    ~DubinsPathPlanner();
    
    // 回调函数
    void gpsCallback(const std_msgs::Float64MultiArray::ConstPtr& msg);
    void yawCallback(const std_msgs::Float32::ConstPtr& msg);
    void targetCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);  
    
    // 主循环
    void run();
    
    // 工具函数
    double normalizeAngle(double angle);
    double distance(double x1, double y1, double x2, double y2);
    Point2D latLonToXY(double lat, double lon, double ref_lat, double ref_lon);
    
    // 计算下一个目标点的坐标
    void calculateNextTargetPoint();
};

bool ref_initialized = false;
double ref_lat_;
double ref_lon_;

#endif // DUBINS_PATH_PLANNER_H