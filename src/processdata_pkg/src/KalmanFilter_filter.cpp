#include "KalmanFilter_filter.h"
#include <cmath>

KalmanFilter::KalmanFilter() : is_initialized_(false), last_timestamp_(0.0), filter_count_(0) {
    // 根据静止数据调整参数
    // 从你的数据看，静止时最大变化约50，实际变化约0.5-2度
    // 测量噪声：反映GPS本身的误差（静止时数据波动）
    measurement_noise_ = 1;      // 测量噪声标准差0.5度
    
    // 过程噪声：反映目标真实运动（静止时应很小）
    position_noise_ = 0.01;        // 位置过程噪声（静止时很小）
    velocity_noise_ = 0.1;         // 速度过程噪声（允许轻微速度变化）
    
    // Initialize matrices
    state_ = Eigen::Vector4d::Zero();
    covariance_ = Eigen::Matrix4d::Identity() * 1.0;  // 减小初始协方差
    
    // State transition matrix (will be updated with dt)
    F_ = Eigen::Matrix4d::Identity();
    
    // Process noise covariance (will be scaled with dt)
    Q_ = Eigen::Matrix4d::Zero();
    
    // Measurement matrix (only measures position)
    H_ = Eigen::Matrix<double, 2, 4>::Zero();
    H_(0, 0) = H_(1, 1) = 1;
    
    // Measurement noise covariance
    R_ = Eigen::Matrix2d::Identity() * (measurement_noise_ * measurement_noise_);
    
    // Identity matrix
    I_ = Eigen::Matrix4d::Identity();
}

void KalmanFilter::init(const Eigen::Vector4d& initial_state) {
    state_ = initial_state;
    is_initialized_ = true;
    filter_count_ = 0;
    
    // 初始化协方差矩阵
    covariance_ = Eigen::Matrix4d::Identity();
    covariance_(0,0) = measurement_noise_ * measurement_noise_;  // 位置初始不确定度
    covariance_(1,1) = measurement_noise_ * measurement_noise_;
    covariance_(2,2) = 1.0;  // 速度初始不确定度
    covariance_(3,3) = 1.0;
}

void KalmanFilter::predict(double dt) {
    if (!is_initialized_) return;
    
    // 限制时间间隔，避免过大或过小
    if (dt > 0.5) dt = 0.5;
    if (dt < 0.001) dt = 0.01;
    
    // 更新状态转移矩阵
    F_.setIdentity();
    F_(0, 2) = dt;  // x = x + vx * dt
    F_(1, 3) = dt;  // y = y + vy * dt
    
    // 动态调整过程噪声协方差（根据时间间隔和运动状态）
    Q_.setZero();
    
    // 位置噪声：随时间和速度不确定性增加
    Q_(0, 0) = position_noise_ * dt;
    Q_(1, 1) = position_noise_ * dt;
    
    // 速度噪声：允许缓慢的速度变化（静止时很小）
    Q_(2, 2) = velocity_noise_ * dt;
    Q_(3, 3) = velocity_noise_ * dt;
    
    // 位置-速度相关性（可选，提高滤波效果）
    double dt2 = dt * dt / 2.0;
    Q_(0, 2) = position_noise_ * dt2;
    Q_(1, 3) = position_noise_ * dt2;
    Q_(2, 0) = position_noise_ * dt2;
    Q_(3, 1) = position_noise_ * dt2;
    
    // 预测状态
    state_ = F_ * state_;
    
    // 预测协方差
    covariance_ = F_ * covariance_ * F_.transpose() + Q_;
}

void KalmanFilter::update(const Eigen::Vector2d& measurement) {
    if (!is_initialized_) return;
    
    // 计算残差
    Eigen::Vector2d y = measurement - H_ * state_;
    
    // 计算残差协方差
    Eigen::Matrix2d S = H_ * covariance_ * H_.transpose() + R_;
    
    // 计算卡尔曼增益
    Eigen::Matrix<double, 4, 2> K = covariance_ * H_.transpose() * S.inverse();
    
    // 更新状态
    state_ = state_ + K * y;
    
    // 更新协方差（使用Joseph形式，数值稳定性更好）
    Eigen::Matrix4d I_KH = I_ - K * H_;
    covariance_ = I_KH * covariance_ * I_KH.transpose() + K * R_ * K.transpose();
    
    // 限制速度范围（静止时速度应该很小）
    if (std::abs(state_(2)) > 10.0) state_(2) = state_(2) > 0 ? 10.0 : -10.0;
    if (std::abs(state_(3)) > 10.0) state_(3) = state_(3) > 0 ? 10.0 : -10.0;
}

Point KalmanFilter::getPosition() const {
    return Point(state_(0), state_(1));
}

Eigen::Vector4d KalmanFilter::getState() const {
    return state_;
}

bool KalmanFilter::isInitialized() const {
    return is_initialized_;
}

void KalmanFilter::setTimestamp(double timestamp) {
    last_timestamp_ = timestamp;
}

void KalmanFilter::reset() {
    is_initialized_ = false;
    state_.setZero();
    covariance_ = Eigen::Matrix4d::Identity() * 1.0;
    filter_count_ = 0;
}

// 卡尔曼滤波处理（保持原有接口，但改进实现）
void KalmanFilter::Kalman_process(Point target_pot) {
    static double last_time = 0.0;
    static bool first_call = true;
    
    // 获取当前时间（秒）
    double current_time = ros::Time::now().toSec();
    
    if (!is_initialized_) {
        // 初始化
        Eigen::Vector4d initial_state;
        initial_state << target_pot.x, target_pot.y, 0.0, 0.0;
        init(initial_state);
        last_time = current_time;
        setTimestamp(current_time);
        filter_count_ = 0;
        ROS_DEBUG("Kalman filter initialized at (%.6f, %.6f)", target_pot.x, target_pot.y);
        return;
    }
    
    // 计算实际时间间隔
    double dt = current_time - last_time;
    
    // 第一次调用或时间间隔异常时的处理
    if (first_call) {
        first_call = false;
        dt = 0.083;  // 使用默认值
    }
    
    // 限制时间间隔范围
    if (dt > 0.5) {
        ROS_WARN_THROTTLE(1, "Large dt detected: %.3f s, limiting to 0.5 s", dt);
        dt = 0.5;
    }
    if (dt < 0.001) {
        dt = 0.01;
    }
    
    // 预测步骤（使用实际时间间隔）
    predict(dt);
    
    // 更新步骤
    Eigen::Vector2d measurement;
    measurement << target_pot.x, target_pot.y;
    update(measurement);
    
    // 更新状态到输出点（可选：如果需要返回滤波后的点）
    // 注意：这个函数目前是void，如果需要返回滤波结果，需要修改接口
    // 这里只是更新了内部状态，可以通过getPosition()获取结果
    
    // 更新时间戳
    last_time = current_time;
    filter_count_++;
    
    // 调试信息：打印速度和位置变化
    if (filter_count_ % 10 == 0) {
        ROS_DEBUG("Filtered pos: (%.4f, %.4f), Vel: (%.4f, %.4f), dt=%.3f", 
                  state_(0), state_(1), state_(2), state_(3), dt);
    }
}

// 全局实例
KalmanFilter kf;