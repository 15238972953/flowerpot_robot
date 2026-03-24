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

#define M_PI 3.14159265358979323846
#define IS_RECORDED 0x80   // STM32发送的标志位，表示完成一次记录
#define IS_NOT_RECORDED 0x00   

static bool ref_initialized = false;     // 是否已初始化参考点,以机器人上电点为参考点，将其他GPS坐标转换为相对于该点的平面坐标
static double ref_lat_;
static double ref_lon_;

struct Point2D {
    double x, y;      // 转换后的平面坐标

    // 静态成员声明（需要在结构体外定义）
    static bool ref_initialized;
    static double ref_lat;
    static double ref_lon;

    Point2D(double x_ = 0, double y_ = 0) : x(x_), y(y_){}

    static Point2D latlon_To_xy(double lat, double lon, double ref_lat, double ref_lon) {
        const double R = 6371000.0; // 地球半径（米）
        double lat_rad = lat * M_PI / 180.0;
        double lon_rad = lon * M_PI / 180.0;
        double ref_lat_rad = ref_lat * M_PI / 180.0;
        double ref_lon_rad = ref_lon * M_PI / 180.0;
        
        double x = R * (lon_rad - ref_lon_rad) * cos(ref_lat_rad);
        double y = R * (lat_rad - ref_lat_rad);
        
        return Point2D(x, y);
    }
};

// 位姿点（包含位置和航向）
struct PosePoint
{
    Point2D point;
    double yaw;      // 航向角
    PosePoint(double x = 0, double y = 0, double yaw_ = 0) : point(x, y), yaw(yaw_) {}
};

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
    
    // 发布者
    ros::Publisher serial_data_pub;

    // 服务
    ros::ServiceServer config_start_service_;
    
    // 参数
    int required_points_;                  // 需要的点数（默认4）
    int record_interval_;               // 记录间隔时间（秒），防止重复记录

    // 当前状态
    PosePoint current_PosePoint_;              // 当前位姿
    
    // 目标点
    Point2D target_point_;               // 目标位置

    // 取花盆坐标
    Point2D pickup_point;                // 取花点坐标

    // 待摆放花盆坐标矩阵，用于记录每个花盆的坐标；
    std::vector<std::vector<Point2D>> target_pots_matrix_; 
    double pot_placement_spacing; // 花盆摆放间距（米）
    enum class PlacementType {
        GRID_PLACEMENT = 0,    // 网格摆放
        TRIANGULAR_PLACEMENT = 1,  // 三角错位摆放
    };
    PlacementType pot_placement_type_ = PlacementType::GRID_PLACEMENT; // 默认摆放方式

    // 状态变量
    std::vector<Point2D> recorded_points_; // 已记录的GPS点
    ros::Time last_record_time_;           // 上次记录时间
    bool gps_flag;                        // GPS标志位（从参数服务器读取）

    // 计算每个花盆的摆放坐标
    void calculatePotsMatrix(
        const std::vector<Point2D>& recorded_points, 
        double pot_placement_spacing,
        PlacementType placement_type = pot_placement_type_);

    Point2D current_pot_coordinate; // 记录当前要抓取的花盆坐标

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

    // 发布执行指令
    common_msgs_pkg::serial_data serial_msg;    //通过串口发送给stm32的数据
    int command;  //用于记录机械臂的指令

    // 抓取命令
    const int COMMAND_GRASP = 0x03;  // 抓取指令
    const int COMMAND_RELEASE = 0x04; // 释放指令
    const int COMMAND_COMMON = 0x05;  // 平常指令
    
    // 回调函数
    void gpsCallback(const std_msgs::Float64MultiArray::ConstPtr& msg);
    void spacingCallback(const std_msgs::Float64::ConstPtr& msg);
    void placementTypeCallback(const std_msgs::Int8::ConstPtr& msg);
    void potCoordsCallback(const std_msgs::Float64MultiArray::ConstPtr& msg);
    void yawCallback(const std_msgs::Float32::ConstPtr& msg);

    // 划定目标区域记录点
    void recordCurrentPosition(const Point2D& point);

    // 计算两点之间的距离
    double distance(Point2D point1, Point2D point2);
    // 获取当前要摆放的目标点
    void getCurrentTargetPoint(const Point2D& target);
    
    bool configstartCallback(decision_making_pkg::StartTransport::Request &req,
                        decision_making_pkg::StartTransport::Response &res);
    
public:
    DecisionMaking();
    ~DecisionMaking();
    
    // 主循环
    void run();
};

#endif // DECISION_MAKING_H