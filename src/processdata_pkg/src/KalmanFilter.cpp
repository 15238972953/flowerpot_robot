#include "KalmanFilter.h"
#include <iostream>
KalmanFilterFusion::KalmanFilterFusion() {
    // 初始化噪声参数
    R_camera_ = Eigen::Matrix2d::Identity() * 0.25;  // 相机噪声较小
    R_radar_ = Eigen::Matrix2d::Identity() * 0.5;   // 雷达噪声较大
}

std::vector<Eigen::Vector2d> KalmanFilterFusion::fusePositions(
        const std::vector<Eigen::Vector2d>& camera_positions,
        const std::vector<Eigen::Vector2d>& radar_positions) {

    std::vector<Eigen::Vector2d> fused_positions;

    // 检查输入数据是否匹配
    if (camera_positions.size() != radar_positions.size()) {
        std::cerr << "Error: Camera and radar data size mismatch!" << std::endl;
        return fused_positions;
    }

    // 对每对关联好的观测进行融合
    for (size_t i = 0; i < camera_positions.size(); ++i) {
        // 计算卡尔曼增益
        Eigen::Matrix2d K = R_radar_ * (R_camera_ + R_radar_).inverse();

        // 融合位置 (简单加权平均)
        Eigen::Vector2d fused_pos = camera_positions[i] +
                                    K * (radar_positions[i] - camera_positions[i]);

        fused_positions.push_back(fused_pos);
    }

    return fused_positions;
}