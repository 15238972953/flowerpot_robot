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

// 二维点结构
struct Point {
    float x;
    float y;
    Point(float _x = 0, float _y = 0);
};

class ProcessDataNode {
public:
    ProcessDataNode();

private:
    void cameradata_Callback(const yolo11_pkg::array::ConstPtr& camera_msg);
    void radardata_Callback(const radar_msgs::array::ConstPtr& radar_msg);

private:
    ros::NodeHandle nh;
    ros::Subscriber radar_processed_sub;
    ros::Subscriber camera_processed_sub;

    // 存储最新数据
    std::vector<Point> camera_points;
    std::vector<Point> radar_points;

    KalmanFilter kf;
};

#endif