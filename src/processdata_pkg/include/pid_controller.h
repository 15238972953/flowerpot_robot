#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include<ros/ros.h>

struct PWM
{
    int PWM_Left;
    int PWM_Right;
    PWM(int _PWM_Left = 90, int _PWM_Right = 90);
};

template <typename T>

class PIDController {
public:
    PIDController(double kp, double ki, double kd);
    int compute_position(T setpoint, T current_value);
    int compute_Incremental(T setpoint, T current_value);

private:
    double kp_;
    double ki_;
    double kd_;
    double prev_error_;
    double integral_;
};

PWM calculatePWM(Eigen::Vector2d filtered_pos, const double target_x = 0.0, const double target_y = 25.0);
PWM calculatePWM( const float yaw_angle, const int extend_y, const float Target_yaw_angle = 180.0, const int Target_extend_y = 480);
#endif    