#include "KalmanFilter.h"
#include <iostream>

KalmanFilter::KalmanFilter() : is_initialized_(false) {
    // 初始化协方差矩阵
    P_ << 1.0, 0.0,
            0.0, 1.0;

    // 过程噪声协方差矩阵 (目标静止，噪声很小)
    Q_ << 0.001, 0.0,
            0.0, 0.001;

    // 观测噪声协方差矩阵
    R_camera_ << 0.1, 0.0,   // 相机精度较高
            0.0, 0.1;

    R_radar_ << 0.2, 0.0,    // 雷达精度较低
            0.0, 0.2;

    I_ = Eigen::Matrix2d::Identity();
}

void KalmanFilter::Init(const Eigen::Vector2d& initial_pos) {
    x_ = initial_pos;
    is_initialized_ = true;
    std::cout << "Filter initialized with position: "
              << x_.transpose() << std::endl;
}

void KalmanFilter::UpdateCamera(const Eigen::Vector2d& z) {
    if (!is_initialized_) {
        Init(z);
        return;
    }

    // 计算卡尔曼增益
    Eigen::Matrix2d S = P_ + R_camera_;
    Eigen::Matrix2d K = P_ * S.inverse();

    // 更新状态和协方差
    x_ = x_ + K * (z - x_);
    P_ = (I_ - K) * P_;
}

void KalmanFilter::UpdateRadar(const Eigen::Vector2d& z) {
    if (!is_initialized_) {
        Init(z);
        return;
    }

    // 计算卡尔曼增益
    Eigen::Matrix2d S = P_ + R_radar_;
    Eigen::Matrix2d K = P_ * S.inverse();

    // 更新状态和协方差
    x_ = x_ + K * (z - x_);
    P_ = (I_ - K) * P_;
}

Eigen::Vector2d KalmanFilter::GetFusedPosition() const {
    return x_;
}