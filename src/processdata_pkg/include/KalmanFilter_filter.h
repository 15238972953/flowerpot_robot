#ifndef KALMAN_FILTER_FILTER_H
#define KALMAN_FILTER_FILTER_H

#include <eigen3/Eigen/Dense>
#include "HungarianAlgorithm.h"
#include "processdata_node.h"
#include <ros/ros.h>

class KalmanFilter {
public:
    KalmanFilter();

    void init(const Eigen::Vector4d& initial_state);
    void predict(double dt);
    void update(const Eigen::Vector2d& measurement);

    Point getPosition() const;
    Eigen::Vector4d getState() const;
    bool isInitialized() const;
    void Kalman_process(Point target_pot);
    
    // 新增：设置时间戳，用于计算实际时间间隔
    void setTimestamp(double timestamp);
    void reset();

private:
    Eigen::Vector4d state_;       // [rel_x, rel_y, rel_vx, rel_vy]
    Eigen::Matrix4d covariance_;
    Eigen::Matrix4d F_;           // State transition matrix
    Eigen::Matrix4d Q_;           // Process noise covariance
    Eigen::Matrix<double, 2, 4> H_; // Measurement matrix
    Eigen::Matrix2d R_;           // Measurement noise covariance
    Eigen::Matrix4d I_;           // Identity matrix
    bool is_initialized_;
    double last_timestamp_;       // 上次处理的时间戳
    int filter_count_;            // 滤波次数计数器
    
    // 参数配置
    double measurement_noise_;    // 测量噪声（根据静止数据调整）
    double position_noise_;       // 位置过程噪声
    double velocity_noise_;       // 速度过程噪声
};

extern KalmanFilter kf;

#endif // KALMAN_FILTER_H