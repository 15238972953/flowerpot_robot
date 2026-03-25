#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <iostream>
#include<ros/ros.h>
#include "point.h"

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
    auto compute_Incremental(double setpoint, double current_value);

private:
    float kp_;
    float ki_;
    float kd_;
    float prev_error_; // 上一次的误差
    float prev_prev_error_; // 用于增量式PID
    float integral_;
};

PWM calculatePWM(Point2D pot_pos, Point2D target_pos);
PWM calculatePWM(double yaw_angle, double Target_yaw_angle);

#endif    