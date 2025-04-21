#ifndef KALMAN_FILTER_FILTER_H
#define KALMAN_FILTER_FILTER_H

#include <eigen3/Eigen/Dense>

class KalmanFilter {
public:
    KalmanFilter();

    void init(const Eigen::Vector4d& initial_state);
    void predict(double dt);
    void update(const Eigen::Vector2d& measurement);

    Eigen::Vector2d getPosition() const;
    Eigen::Vector4d getState() const;
    bool isInitialized() const;
    void Kalman_process(); 

private:
    Eigen::Vector4d state_;       // [rel_x, rel_y, rel_vx, rel_vy] (相对机器人的位置和速度)
    Eigen::Matrix4d covariance_;
    Eigen::Matrix4d F_;           // State transition matrix
    Eigen::Matrix4d Q_;           // Process noise covariance
    Eigen::Matrix<double, 2, 4> H_; // Measurement matrix
    Eigen::Matrix2d R_;           // Measurement noise covariance
    Eigen::Matrix4d I_;           // Identity matrix
    bool is_initialized_;
};

#endif // KALMAN_FILTER_H