#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <iostream>

class PIDController {
public:
    PIDController(double kp, double ki, double kd);
    double compute(double setpoint, double current_value, double dt);
    void calculatePWM(const Position& robot, double& left_pwm, double& right_pwm);

private:
    double kp_;
    double ki_;
    double kd_;
    double prev_error_;
    double integral_;
};

#endif    