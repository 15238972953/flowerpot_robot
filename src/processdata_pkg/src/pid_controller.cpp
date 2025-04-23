#include "pid_controller.h"

PWM::PWM(int p1, int p2) : PWM_Left(p1), PWM_Right(p2) {}

PIDController::PIDController(double kp, double ki, double kd)
    : kp_(kp), ki_(ki), kd_(kd), prev_error_(0), integral_(0) {}

double PIDController::compute_X(double setpoint, double current_X_value) {
    double error = current_X_value - setpoint;
    integral_ += error;
    double derivative = (error - prev_error_);
    double output = kp_ * error + ki_ * integral_ + kd_ * derivative;
    prev_error_ = error;
    return output;
}   

double PIDController::compute_Y(double setpoint, double current_Y_value) {
    double error = current_Y_value - setpoint;
    if (error > 40)
    {
        return 90;
    }else{
        integral_ += error;
        double derivative = (error - prev_error_);
        double output = kp_ * error + ki_ * integral_ + kd_ * derivative;
        prev_error_ = error;
        return output;
    }
} 

// 计算左右电机的PWM值
PWM calculatePWM(Eigen::Vector2d filtered_pos, const double target_x, const double target_y) {
    PWM PWM_Value;
    // 初始化PID控制器，x和y方向分别使用不同的PID参数
    PIDController pid_x(1, 0.1, 0.01);
    PIDController pid_y(2, 0.1, 0.01);

    // 使用PID控制器计算x和y方向的输出
    double output_x = pid_x.compute_X(target_x, filtered_pos.x());
    double output_y = pid_y.compute_Y(target_y, filtered_pos.y());
    // ROS_INFO("output:%.3f,%.3f", output_x, output_y);
    // 根据x和y方向的输出计算左右电机的PWM值
    // 这里简单地将x方向的输出用于转向控制，y方向的输出用于前进后退控制
    int left_pwm = output_y + output_x;
    int right_pwm = output_y - output_x;

    // 限制PWM值在0到255之间
    if (left_pwm < -127) left_pwm = -127;
    if (left_pwm > 127) left_pwm = 127;
    if (right_pwm < -127) right_pwm = -127;
    if (right_pwm > 127) right_pwm = 127;
    PWM_Value.PWM_Left = left_pwm;
    PWM_Value.PWM_Right = right_pwm;
    return PWM_Value;
}

