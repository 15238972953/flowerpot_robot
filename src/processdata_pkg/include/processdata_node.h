#ifndef PROCESSDATA_NODE_H
#define PROCESSDATA_NODE_H

#include<ros/ros.h>
#include<radar_msgs/array.h>
#include<radar_msgs/radar.h>
#include<yolo11_pkg/coordinate.h>
#include<yolo11_pkg/array.h>
#include<cmath>
#include "HungarianAlgorithm.h"
#include "KalmanFilter.h"

struct PWM
{
    int PWM_Left;
    int PWM_Right;
    PWM(int _PWM_Left = 0, _PWM_Right = 0);
};


class ProcessDataNode {
public:
    ProcessDataNode();

private:
    void cameradata_Callback(const yolo11_pkg::array::ConstPtr& camera_msg);
    void radardata_Callback(const radar_msgs::array::ConstPtr& radar_msg);
    Point selectClosestPot(const std::vector<Point>& pots);

private:
    ros::NodeHandle nh;
    ros::Subscriber radar_processed_sub;
    ros::Subscriber camera_processed_sub;

    // 存储最新数据
    std::vector<Point> camera_points;
    std::vector<Point> tmp_camera_points;
    std::vector<Point> radar_points;

    std::vector<Point> camera_matchs, radar_matchs;  //保存匹配后的数据
    std::vector<Point> fused_matchs;   //保存融合后的数据
    KalmanFilterFusion fuser;   //融合相机和雷达的滤波器
    KalmanFilter kf;      //最近目标的靠近滤波器
};

#endif