#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include<ros/ros.h>

struct PWM
{
    int PWM_Left;
    int PWM_Right;
    PWM(int _PWM_Left = 0, int _PWM_Right = 0);
};

class PIDController {
public:
    PIDController(double kp, double ki, double kd);
    double compute_X(double setpoint, double current_value);
    double compute_Y(double setpoint, double current_value);

private:
    double kp_;
    double ki_;
    double kd_;
    double prev_error_;
    double integral_;
};

PWM calculatePWM(Eigen::Vector2d filtered_pos, const double target_x = 0.0, const double target_y = 25.0);

#endif    