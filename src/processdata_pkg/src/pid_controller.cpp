#include "pid_controller.h"

PIDController::PIDController(double kp, double ki, double kd)
    : kp_(kp), ki_(ki), kd_(kd), prev_error_(0), integral_(0) {}

double PIDController::compute(double setpoint, double current_value) {
    double error = setpoint - current_value;
    integral_ += error;
    double derivative = (error - prev_error_);
    double output = kp_ * error + ki_ * integral_ + kd_ * derivative;
    prev_error_ = error;
    return output;
}    

// 计算左右电机的PWM值
PWM PIDController::calculatePWM(Eigen::Vector2d filtered_pos, const double target_x = 0, const double target_y = 25) {
    // 初始化PID控制器，x和y方向分别使用不同的PID参数
    PIDController pid_x(1.0, 0.1, 0.01);
    PIDController pid_y(1.0, 0.1, 0.01);

    // 使用PID控制器计算x和y方向的输出
    double output_x = pid_x.compute(target_x, filtered_pos.x);
    double output_y = pid_y.compute(target_y, filtered_pos.y);

    // 根据x和y方向的输出计算左右电机的PWM值
    // 这里简单地将x方向的输出用于转向控制，y方向的输出用于前进后退控制
    left_pwm = output_y - output_x;
    right_pwm = output_y + output_x;

    // 限制PWM值在0到255之间
    if (left_pwm < 0) left_pwm = 0;
    if (left_pwm > 255) left_pwm = 255;
    if (right_pwm < 0) right_pwm = 0;
    if (right_pwm > 255) right_pwm = 255;

    return {left_pwm,right_pwm};
}

