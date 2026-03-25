// decision_making.h
#ifndef DECISION_MAKING_H
#define DECISION_MAKING_H

#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Bool.h>
#include <vector>
#include <string>
#include "decision_making_pkg/StartTransport.h"
#include <common_msgs_pkg/serial_data.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int8.h>
#include "pid_controller.h"

#define M_PI 3.14159265358979323846
#define IS_RECORDED 0x80   // STM32发送的标志位，表示完成一次记录
#define IS_NOT_RECORDED 0x00   

#define GPS_TO_POTPOINT_DISTANCE 0.527 // 机器人GPS定位与花盆实际坐标距离
#define Lidar_TO_POTPOINT_DISTANCE 0.2   // 激光雷达与花盆实际坐标距离
static bool ref_initialized = false;     // 是否已初始化参考点,以机器人上电点为参考点，将其他GPS坐标转换为相对于该点的平面坐标
static double ref_lat_;
static double ref_lon_;

struct RectangleArea {
    // 四个点，顺序：左上、右上、右下、左下
    // |（第一个点）-----------（第二个点）
    // |  o o o                      |
    // |                             |
    // |                             |
    // |                             |
    // |                             |
    // |                             |
    // |                             |
    // |                             |
    // |                             |
    // |                             |
    // |                             |
    // |（第四个点）-----------（第三个点）
    std::vector<Point2D> points;  
    bool is_complete;
    
    RectangleArea() : is_complete(false) {}
    
    // 检查矩形是否有效（四个点都不为空）
    bool isValid() const {
        return points.size() == 4;
    }
    
    // 清空矩形
    void clear() {
        points.clear();
        is_complete = false;
    }
    
    // 打印矩形信息
    void print() const {
        if (points.size() != 4) {
            ROS_WARN("矩形未完成，当前点数: %zu", points.size());
            return;
        }
        
        ROS_INFO("========== 目标区域矩形 ==========");
        ROS_INFO("点1 (左下): %.3f, %.3f", points[0].x, points[0].y);
        ROS_INFO("点2 (右下): %.3f, %.3f", points[1].x, points[1].y);
        ROS_INFO("点3 (右上): %.3f, %.3f", points[2].x, points[2].y);
        ROS_INFO("点4 (左上): %.3f, %.3f", points[3].x, points[3].y);
        ROS_INFO("=================================");
    }
};

class DecisionMaking {
private:
    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
    
    // 订阅者
    ros::Subscriber gps_sub_;
    ros::Subscriber pot_coords_sub_; // 订阅花盆坐标的订阅者
    ros::Subscriber yaw_sub_;       // 订阅偏航角（从IMU获取）
    ros::Subscriber grasped_pub_;   // 订阅抓取完成标志位
    ros::Subscriber released_pub_;  // 订阅释放完成标志位
    // 发布者
    ros::Publisher serial_data_pub;
    ros::Publisher transported_pot_count_pub;  // 发布已搬运花盆数量
    // 服务
    ros::ServiceServer config_start_service_;

private:
    // 参数
    int required_points_;                  // 需要的点数（默认4）
    int record_interval_;               // 记录间隔时间（秒），防止重复记录
    double pot_placement_spacing; // 花盆摆放间距（米）

    enum class PlacementType {
        GRID_PLACEMENT = 0,    // 网格摆放
        TRIANGULAR_PLACEMENT = 1,  // 三角错位摆放
    };

    PlacementType pot_placement_type_ = PlacementType::GRID_PLACEMENT; // 默认摆放方式

private:
    // 当前状态
    PosePoint current_PosePoint_;              // 当前位姿
    // 目标点
    Point2D target_point_;               // 目标位置

    // 待摆放花盆坐标矩阵，用于记录每个花盆的坐标；
    std::vector<std::vector<Point2D>> target_pots_matrix_; 
    int total_targets;                   // 总的可摆放目标点数量

    // 状态变量
    std::vector<Point2D> recorded_points_; // 已记录的GPS点
    ros::Time last_record_time_;           // 上次记录时间
    bool gps_flag;                        // GPS标志位（从参数服务器读取）

    Point2D current_pot_coordinate; // 记录当前要抓取的花盆坐标

    bool grasped_status = false; // 抓取完成状态
    bool released_status = false; // 释放完成状态

    // 搬运状态
    enum class TaskState {
        WAITING_START,      // 等待开始信号
        MOVING_TO_PICKUP,   // 移动到取花点
        PICKING_UP,         // 取花中
        MOVING_TO_PLACE,    // 移动到摆放点
        PLACING,            // 摆放花盆
        TASK_COMPLETE       // 任务完成
    };
    TaskState current_state;

    // 当前搬运的目标点索引,同时也表示已搬运花盆数量
    int current_target_index = 0;
    std_msgs::Int8 count_msg;

private:
    // 发布执行指令
    common_msgs_pkg::serial_data serial_msg;    //通过串口发送给stm32的数据
    int command;  //用于记录机械臂的指令

    // 抓取命令
    const int COMMAND_GRASP = 0x03;  // 抓取指令
    const int COMMAND_RELEASE = 0x04; // 释放指令
    const int COMMAND_COMMON = 0x05;  // 平常指令

private:
    // 回调函数
    void gpsCallback(const std_msgs::Float64MultiArray::ConstPtr& msg);
    void potCoordsCallback(const std_msgs::Float64MultiArray::ConstPtr& msg);
    void yawCallback(const std_msgs::Float32::ConstPtr& msg);
    void graspedStatusCallback(const std_msgs::Bool::ConstPtr& msg);
    void releasedStatusCallback(const std_msgs::Bool::ConstPtr& msg);

    // 划定目标区域记录点
    void recordCurrentPosition(const Point2D& point);

    // 计算两点之间的距离
    double distance(Point2D point1, Point2D point2);
    // 获取当前要摆放的目标点
    Point2D getCurrentTargetPoint();

    bool configstartCallback(decision_making_pkg::StartTransport::Request &req,
                        decision_making_pkg::StartTransport::Response &res);
    
    // 计算每个花盆的摆放坐标
    void calculatePotsMatrix(
        const std::vector<Point2D>& recorded_points, 
        double pot_placement_spacing,
        PlacementType placement_type = PlacementType::GRID_PLACEMENT);
    
    // 等待开始信号
    void WAITING_START_State();
    // 移动到取花点
    void MOVING_TO_PICKUP_State();
    // 取花中
    void PICKING_UP_State();
    // 移动到摆放点
    void MOVING_TO_PLACE_State();
    // 摆放花盆
    void PLACING_State();
    // 任务完成
    void TASK_COMPLETE_State();
public:
    DecisionMaking();
    ~DecisionMaking();
    
    // 主循环
    void run();
};

#endif // DECISION_MAKING_H