#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#include <Eigen/Dense>

class KalmanFilter {
public:
    KalmanFilter();

    // 初始化滤波器
    void Init(const Eigen::Vector2d& initial_pos);

    // 更新步骤 (相机观测)
    void UpdateCamera(const Eigen::Vector2d& z);

    // 更新步骤 (雷达观测)
    void UpdateRadar(const Eigen::Vector2d& z);

    // 获取融合后的位置
    Eigen::Vector2d GetFusedPosition() const;

private:
    // 状态向量 [x, y]
    Eigen::Vector2d x_;

    // 状态协方差矩阵
    Eigen::Matrix2d P_;

    // 过程噪声协方差矩阵
    Eigen::Matrix2d Q_;

    // 观测噪声协方差矩阵
    Eigen::Matrix2d R_camera_;  // 相机
    Eigen::Matrix2d R_radar_;   // 雷达

    // 单位矩阵
    Eigen::Matrix2d I_;

    bool is_initialized_;
};

#endif // KALMAN_FILTER_H