#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include<ros/ros.h>

#define BASE_SPEED 80  // 基础速度

struct PWM
{
    int PWM_Left;
    int PWM_Right;
    PWM(int _PWM_Left = 0, int _PWM_Right = 0);
};

class PIDController {
public:
    PIDController(float kp, float ki, float kd)
    : kp_(kp), ki_(ki), kd_(kd), prev_prev_error_(0.0), prev_error_(0.0), integral_(0.0) {}
    
    auto compute_position(double setpoint, double current_value);
    auto compute_position(float setpoint, float current_value);
    auto compute_Incremental(float setpoint, float current_value);
    auto compute_Incremental(int setpoint, int current_value);

private:
    float kp_;
    float ki_;
    float kd_;
    float prev_error_; // 上一次的误差
    float prev_prev_error_; // 用于增量式PID
    float integral_;
};

PWM calculatePWM(Eigen::Vector2d filtered_pos, const double target_x = 0.0, const double target_y = 25.0);
PWM calculatePWM( const float yaw_angle, const int extend_y, const float Target_yaw_angle = 180.0, const int Target_extend_y = 480);
PWM calculatePWM(const float yaw_angle, const float Target_yaw_angle);
#endif    