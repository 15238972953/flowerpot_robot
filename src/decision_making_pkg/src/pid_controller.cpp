#include "pid_controller.h"

#define M_PI 3.14159265358979323846
#define Lidar_TO_POTPOINT_DISTANCE 0.2   // 激光雷达与花盆实际坐标距离

PWM::PWM(int p1, int p2) : PWM_Left(p1), PWM_Right(p2) {}   

auto PIDController::compute_position(double setpoint, double current_X_value) {
    double error = current_X_value - setpoint;
    integral_ += error;
    double derivative = (error - prev_error_);
    double output = kp_ * error + ki_ * integral_ + kd_ * derivative;
    prev_error_ = error;
    return output;  // 返回控制量
}

// 增量式PID控制器
auto PIDController::compute_Incremental(double setpoint, double current_value) {
    double error = current_value - setpoint;
    double delta_u = kp_*(error - prev_error_) 
                   + ki_*error 
                   + kd_*(error - 2*prev_error_ + prev_prev_error_);
    
    prev_prev_error_ = prev_error_;
    prev_error_ = error;
    return delta_u;  // 返回的是控制量的增量
}



// 在抓取花盆时，计算左右电机的PWM值
PWM calculatePWM_linear(Point2D pot_pos, Point2D target_pos) {
    PWM PWM_Value;
    // 初始化PID控制器，x和y方向分别使用不同的PID参数
    PIDController pid_x(1.0, 0.1, 0.01);
    PIDController pid_y(2.0, 0.1, 0.01);

    // 使用PID控制器计算x和y方向的输出
    int output_x = pid_x.compute_position(target_pos.x, pot_pos.x);
    int output_y = std::max(pid_y.compute_position(target_pos.y, pot_pos.y), 90.0);   // 后面调试中如果跟原来不一样，看一下这里compute_Y
    // ROS_INFO("output:%.3f,%.3f", output_x, output_y);
    // 根据x和y方向的输出计算左右电机的PWM值
    // 这里简单地将x方向的输出用于转向控制，y方向的输出用于前进后退控制
    int left_pwm = output_y + output_x;
    int right_pwm = output_y - output_x;

    // 限制PWM值在-127到127之间
    if (left_pwm < -127) left_pwm = -127;
    if (left_pwm > 127) left_pwm = 127;
    if (right_pwm < -127) right_pwm = -127;
    if (right_pwm > 127) right_pwm = 127;
    PWM_Value.PWM_Left = left_pwm;
    PWM_Value.PWM_Right = right_pwm;
    return PWM_Value;
}

// 输入只有yaw时(调整机器人的角度)，计算左右电机的PWM值
PWM calculatePWM_angular(double yaw_angle, double Target_yaw_angle) {
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

/**
 * 计算当前自车坐标系下的目标点位置
 * 每一帧都会重新计算，因为小车在运动
 */
Point2D getTargetInVehicleFrame(const PosePoint& current, const Point2D& target) {
    // 计算相对位置（世界坐标系）
    double dx = target.x - current.point.x;
    double dy = target.y - current.point.y;
    
    // 转换到自车坐标系（x向右，y向前）
    double vehicle_x = dx * cos(current.yaw) - dy * sin(current.yaw);
    double vehicle_y = dx * sin(current.yaw) + dy * cos(current.yaw);
    
    return Point2D(vehicle_x, vehicle_y);
}

/**
 * 计算PWM控制量（支持原地旋转和PID控制）
 * @param target 目标点
 * @param current 当前位置和姿态
 * @return PWM控制量
 */
PWM calculatePWM(const PosePoint& current, const Point2D& target) {
    
    // 1. 将目标点转换到当前自车坐标系（每一帧都重新计算）
    Point2D target_relative_point = getTargetInVehicleFrame(current, target);
    
    // 2. 在自车坐标系下，目标点的坐标含义
    double target_relative_forward = target_relative_point.y;   // 前方距离（正=在前，负=在后）
    double target_relative_lateral = target_relative_point.x;   // 横向偏差（正=在右，负=在左）
    double distance = sqrt(target_relative_forward * target_relative_forward 
                            + target_relative_lateral * target_relative_lateral);
    
    // 3. 计算需要转动的角度（自车坐标系下）
    double target_relative_angle = atan2(target_relative_lateral, target_relative_forward);

    // 5. 判断是否需要优先旋转
    const double ANGLE_THRESHOLD = 0.5;  // 约30度的角度阈值
    if (fabs(target_relative_angle) > ANGLE_THRESHOLD && distance > 0.3) {
        // 模式1：原地旋转对准目标
        return calculatePWM_angular(target_relative_angle * 180.0f / M_PI, 0.0);
    } else {
        // 模式2：前进并微调方向
        return calculatePWM_linear(target_relative_point, Point2D(0.0, Lidar_TO_POTPOINT_DISTANCE));  // 以自车坐标系原点为目标点，计算PWM
    }
}


// 巡线行驶时，计算左右电机的PWM值
// PWM calculatePWM(const float yaw_angle, const int extend_y, const float Target_yaw_angle, const int Target_extend_y) {
//     PWM PWM_Value;
//     // 初始化PID控制器，x和y方向分别使用不同的PID参数
//     PIDController pid_yaw(1.0f, 0.1f, 0.01f);
//     PIDController pid_e_y(0.5f, 0.1f, 0.01f);

//     // 使用PID控制器计算x和y方向的输出
//     auto yaw_pwm = pid_yaw.compute_Incremental(Target_yaw_angle, yaw_angle);
//     auto line_pwm = pid_e_y.compute_Incremental(Target_extend_y, extend_y);  
//     // ROS_INFO("output:%.3f,%.3f", output_x, output_y);
//     // 根据yaw和line的输出计算左右电机的PWM值
//     int left_pwm = BASE_SPEED + static_cast<int>(line_pwm + yaw_pwm);
//     int right_pwm = BASE_SPEED + static_cast<int>(-line_pwm - yaw_pwm);

//     // 限制PWM值在0到255之间
//     if (left_pwm < -127) left_pwm = -127;
//     if (left_pwm > 127) left_pwm = 127;
//     if (right_pwm < -127) right_pwm = -127;
//     if (right_pwm > 127) right_pwm = 127;
//     PWM_Value.PWM_Left = left_pwm;
//     PWM_Value.PWM_Right = right_pwm;
//     return PWM_Value;
// }
