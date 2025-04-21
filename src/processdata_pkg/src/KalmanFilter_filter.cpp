#include "KalmanFilter_filter.h"

KalmanFilter::KalmanFilter() : is_initialized_(false) {
    // Initialize matrices
    state_ = Eigen::Vector4d::Zero();
    covariance_ = Eigen::Matrix4d::Identity() * 10;

    // State transition matrix (constant velocity model)
    F_ = Eigen::Matrix4d::Identity();

    // Process noise covariance
    Q_ = Eigen::Matrix4d::Zero();
    Q_(0, 0) = Q_(1, 1) = 0.1;  // Position noise
    Q_(2, 2) = Q_(3, 3) = 0.5;  // Velocity noise

    // Measurement matrix (only measures position)
    H_ = Eigen::Matrix<double, 2, 4>::Zero();
    H_(0, 0) = H_(1, 1) = 1;

    // Measurement noise
    R_ = Eigen::Matrix2d::Identity() * 0.25;

    // Identity matrix
    I_ = Eigen::Matrix4d::Identity();
}

void KalmanFilter::init(const Eigen::Vector4d& initial_state) {
    state_ = initial_state;
    is_initialized_ = true;
}

void KalmanFilter::predict(double dt) {
    if (!is_initialized_) return;

    // Update state transition matrix with dt
    F_(0, 2) = F_(1, 3) = dt;

    // Predict state (相对位置和速度会随时间变化)
    state_ = F_ * state_;

    // Predict covariance
    covariance_ = F_ * covariance_ * F_.transpose() + Q_;
}

void KalmanFilter::update(const Eigen::Vector2d& measurement) {
    if (!is_initialized_) return;

    // Kalman gain
    Eigen::Matrix<double, 4, 2> K = covariance_ * H_.transpose() *
                                    (H_ * covariance_ * H_.transpose() + R_).inverse();

    // Update state
    state_ = state_ + K * (measurement - H_ * state_);

    // Update covariance
    covariance_ = (I_ - K * H_) * covariance_;
}

Eigen::Vector2d KalmanFilter::getPosition() const {
    return state_.head<2>();
}

Eigen::Vector4d KalmanFilter::getState() const {
    return state_;
}

bool KalmanFilter::isInitialized() const {
    return is_initialized_;
}

// 卡尔曼滤波处理
void KalmanFilter::Kalman_process() {
    if (!kf.isInitialized()) {
        Eigen::Vector4d initial_state;
        initial_state << target_pot.x, target_pot.y, 0.0, 0.0; // 初始相对速度为0
        kf.init(initial_state);
    } else {
        // 预测步骤 (时间间隔假设为0.1秒)
        kf.predict(0.083);

        // 更新步骤
        Eigen::Vector2d measurement;
        measurement << target_pot.x, target_pot.y;
        kf.update(measurement);
    }
}