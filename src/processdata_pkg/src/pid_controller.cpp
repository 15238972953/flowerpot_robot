#include "pid_controller.h"

PWM::PWM(int p1, int p2) : PWM_Left(p1), PWM_Right(p2) {}   

// double PIDController::compute_Y(double setpoint, double current_Y_value) {
//     double error = current_Y_value - setpoint;
//     if (error > 40)
//     {
//         return 90;
//     }else{
//         integral_ += error;
//         double derivative = (error - prev_error_);
//         double output = kp_ * error + ki_ * integral_ + kd_ * derivative;
//         prev_error_ = error;
//         return output;
//     }
// } 

// 位置式PID控制器
auto PIDController::compute_position(double setpoint, double current_X_value) {
    float error = current_X_value - setpoint;
    integral_ += error;
    float derivative = (error - prev_error_);
    float output = kp_ * error + ki_ * integral_ + kd_ * derivative;
    prev_error_ = error;
    return output;  // 返回控制量
}
auto PIDController::compute_position(float setpoint, float current_X_value) {
    float error = current_X_value - setpoint;
    integral_ += error;
    float derivative = (error - prev_error_);
    float output = kp_ * error + ki_ * integral_ + kd_ * derivative;
    prev_error_ = error;
    return output;  // 返回控制量
}

// 增量式PID控制器
auto PIDController::compute_Incremental(float setpoint, float current_value) {
    float error = current_value - setpoint;
    float delta_u = kp_*(error - prev_error_) 
                   + ki_*error 
                   + kd_*(error - 2*prev_error_ + prev_prev_error_);
    
    prev_prev_error_ = prev_error_;
    prev_error_ = error;
    return delta_u;  // 返回的是控制量的增量
}
auto PIDController::compute_Incremental(int setpoint, int current_value) {
    int error = current_value - setpoint;
    int delta_u = kp_*(error - prev_error_) 
                   + ki_*error 
                   + kd_*(error - 2*prev_error_ + prev_prev_error_);
    
    prev_prev_error_ = prev_error_;
    prev_error_ = error;
    return delta_u;  // 返回的是控制量的增量
}

// 在抓取和放置花盆时，计算左右电机的PWM值
PWM calculatePWM(Eigen::Vector2d filtered_pos, const double target_x, const double target_y) {
    PWM PWM_Value;
    // 初始化PID控制器，x和y方向分别使用不同的PID参数
    PIDController pid_x(1.0, 0.1, 0.01);
    PIDController pid_y(2.0, 0.1, 0.01);

    // 使用PID控制器计算x和y方向的输出
    int output_x = pid_x.compute_position(target_x, static_cast<double>(filtered_pos.x()));
    int output_y = std::max(pid_y.compute_position(target_y, static_cast<double>(filtered_pos.y())), 90.0f);   // 后面调试中如果跟原来不一样，看一下这里compute_Y
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

// 巡线行驶时，计算左右电机的PWM值
PWM calculatePWM(const float yaw_angle, const int extend_y, const float Target_yaw_angle, const int Target_extend_y) {
    PWM PWM_Value;
    // 初始化PID控制器，x和y方向分别使用不同的PID参数
    PIDController pid_yaw(1.0f, 0.1f, 0.01f);
    PIDController pid_e_y(0.5f, 0.1f, 0.01f);

    // 使用PID控制器计算x和y方向的输出
    auto yaw_pwm = pid_yaw.compute_Incremental(Target_yaw_angle, yaw_angle);
    auto line_pwm = pid_e_y.compute_Incremental(Target_extend_y, extend_y);  
    // ROS_INFO("output:%.3f,%.3f", output_x, output_y);
    // 根据yaw和line的输出计算左右电机的PWM值
    int left_pwm = BASE_SPEED + static_cast<int>(line_pwm + yaw_pwm);
    int right_pwm = BASE_SPEED + static_cast<int>(-line_pwm - yaw_pwm);

    // 限制PWM值在0到255之间
    if (left_pwm < -127) left_pwm = -127;
    if (left_pwm > 127) left_pwm = 127;
    if (right_pwm < -127) right_pwm = -127;
    if (right_pwm > 127) right_pwm = 127;
    PWM_Value.PWM_Left = left_pwm;
    PWM_Value.PWM_Right = right_pwm;
    return PWM_Value;
}

// 输入只有yaw时，计算左右电机的PWM值
PWM calculatePWM(const float yaw_angle, const float Target_yaw_angle) {
    PWM PWM_Value;
    // 初始化PID控制器，x和y方向分别使用不同的PID参数
    PIDController pid_yaw(1.0f, 0.1f, 0.01f);

    // 使用PID控制器计算x和y方向的输出  
    auto yaw_pwm = pid_yaw.compute_position(Target_yaw_angle, yaw_angle);  
    // ROS_INFO("output:%.3f,%.3f", output_x, output_y);
    // 根据yaw和line的输出计算左右电机的PWM值
    int left_pwm = -yaw_pwm;
    int right_pwm = yaw_pwm;

    // 限制PWM值在0到255之间
    if (left_pwm < -127) left_pwm = -127;
    if (left_pwm > 127) left_pwm = 127;
    if (right_pwm < -127) right_pwm = -127;
    if (right_pwm > 127) right_pwm = 127;
    PWM_Value.PWM_Left = left_pwm;
    PWM_Value.PWM_Right = right_pwm;
    return PWM_Value;
}

