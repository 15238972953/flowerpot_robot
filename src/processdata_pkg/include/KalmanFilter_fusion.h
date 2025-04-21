#ifndef KALMAN_FILTER_FUSION_H
#define KALMAN_FILTER_FUSION_H

#include "HungarianAlgorithm.h"
#include <vector>
#include <eigen3/Eigen/Dense>

class KalmanFilterFusion {
public:
    KalmanFilterFusion();

    // 融合关联好的相机和雷达位置
    std::vector<Eigen::Vector2d> fusePositions(
            const std::vector<Eigen::Vector2d>& camera_positions,
            const std::vector<Eigen::Vector2d>& radar_positions);

private:
    // 相机观测噪声协方差
    Eigen::Matrix2d R_camera_;

    // 雷达观测噪声协方差
    Eigen::Matrix2d R_radar_;
};

#endif // KALMAN_FILTER_FUSION_H