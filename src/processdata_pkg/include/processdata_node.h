#ifndef PROCESSDATA_NODE_H
#define PROCESSDATA_NODE_H

#include <ros/ros.h>
#include <radar_msgs/array.h>
#include <radar_msgs/radar.h>
#include <yolo11_pkg/coordinate.h>
#include <yolo11_pkg/array.h>
#include <cmath>
// #include <common_msgs_pkg/serial_data.h>
#include "HungarianAlgorithm.h"
#include "KalmanFilter_fusion.h"
#include "KalmanFilter_filter.h"
#include <tracking_pkg/track.h>
#include "track_transform.h"
#include "std_msgs/Float32.h" 
#include <common_msgs_pkg/encoder.h>
#include <std_msgs/Float64MultiArray.h>

class ProcessDataNode {
public:

public:
    ProcessDataNode();
    void run();   // 主循环

private:
    void cameradata_Callback(const yolo11_pkg::array::ConstPtr& camera_msg);
    void radardata_Callback(const radar_msgs::array::ConstPtr& radar_msg);
    Point selectClosestPot(const std::vector<Point>& pots);
    // void trackdata_Callback(const tracking_pkg::track::ConstPtr& track_msg);
    void yawdata_Callback(const std_msgs::Float32::ConstPtr& yaw_msg);
    // int extendLineCoordinates(const tracking_pkg::track::ConstPtr& track_msg);
    // void encoderdata_Callback(const common_msgs_pkg::encoder::ConstPtr& encoder_msg);

private:
    ros::NodeHandle nh;
    ros::Subscriber radar_processed_sub;
    ros::Subscriber camera_processed_sub;
    // ros::Subscriber track_processed_sub;
    // ros::Publisher serial_data_pub;
    ros::Publisher pot_coords_pub;      // 发布花盆坐标的发布者
    ros::Subscriber yaw_processed_sub; 
    // ros::Subscriber encoder_processed_sub;

    // 存储最新数据
    std::vector<Point> camera_points;
    std::vector<Point> radar_points;

    std::vector<Eigen::Vector2d> camera_matchs, radar_matchs;  //保存匹配后的数据
    std::vector<Eigen::Vector2d> fused_matchs;   //保存融合后的数据
    KalmanFilterFusion fuser;   //融合相机和雷达的滤波器
     
    // common_msgs_pkg::serial_data serial_msg;    //通过串口发送给stm32的数据
    // int command;  //用于记录机械臂的指令

    PerspectiveTransformer transformer;

    float yaw_angle; // 记录当前的yaw角度
    int extend_Y; // 用于存储延长后的y坐标
    float encoder_diatance = 0.0; // 记录编码器的距离

    Point camera_pot;   // 相机当前坐标点
    Point target_pot;   // 存储融合后的目标点

    // // 抓取命令
    // const int COMMAND_GRASP = 0x03;  // 抓取指令
    // const int COMMAND_RELEASE = 0x04; // 释放指令
    // const int COMMAND_COMMON = 0x05;  // 平常指令
};

std::vector<Point> convert(const std::vector<Eigen::Vector2d> eigenVectors);

#endif