#include "processdata_node.h"
#include <utility>

KalmanFilter kf;      //最近目标的靠近滤波器

std::vector<Point> convert(const std::vector<Eigen::Vector2d> eigenVectors) {
    std::vector<Point> points(eigenVectors.size());
    std::transform(eigenVectors.begin(), eigenVectors.end(), points.begin(),
                    [](const Eigen::Vector2d& vec) { return Point{static_cast<float>(vec[0]), static_cast<float>(vec[1])}; });
    return points;
    }

ProcessDataNode::ProcessDataNode() {
    // 初始化订阅者
    radar_processed_sub = nh.subscribe("Array_Radar", 1000, &ProcessDataNode::radardata_Callback, this);
    camera_processed_sub = nh.subscribe("yolo11_data", 1000, &ProcessDataNode::cameradata_Callback, this);
    track_processed_sub = nh.subscribe("track_msg", 1000, &ProcessDataNode::trackdata_Callback, this);
    yaw_processed_sub = nh.subscribe("/yaw_angle", 1000, &ProcessDataNode::yawdata_Callback, this);
    encoder_processed_sub = nh.subscribe("encoder_msg", 1000, &ProcessDataNode::encoderdata_Callback, this);
    //初始化发布者
    serial_data_pub = nh.advertise<common_msgs_pkg::serial_data>("serial_data", 1000);
}

// 选择最近的花盆
Point ProcessDataNode::selectClosestPot(const std::vector<Point>& pots) {
    if (pots.empty()) return {0, 0};

    Point closest = pots[0];
    double min_dist = std::hypot(closest.x, closest.y);

    for (const auto& pot : pots) {
        double dist = std::hypot(pot.x, pot.y);
        if (dist < min_dist) {
            min_dist = dist;
            closest = pot;
        }
    }

    return closest;
}

void ProcessDataNode::encoderdata_Callback(const common_msgs_pkg::encoder::ConstPtr& encoder_msg)
{
    float left_distance = encoder_msg->left_distance;  // 左轮编码器数据
    float right_distance = encoder_msg->right_distance;  // 右轮编码器数据
    encoder_diatance = (left_distance + right_distance) / 2.0;
}

void ProcessDataNode::yawdata_Callback(const std_msgs::Float32::ConstPtr& yaw_msg) 
{
    // 处理接收到的yaw数据
    yaw_angle = yaw_msg->data;
    // 这里可以添加对yaw_angle的处理逻辑
    // ROS_INFO("Received yaw angle: %.2f", yaw_angle);
}

// 将直线坐标转为延长后的直线坐标
int ProcessDataNode::extendLineCoordinates(const tracking_pkg::track::ConstPtr& track_msg) 
{
    int16_t x1 = track_msg->line[0];  // 第1个元素
    int16_t y1 = track_msg->line[1];  // 第2个元素
    int16_t x2 = track_msg->line[2];  // 第3个元素
    int16_t y2 = track_msg->line[3];  // 第4个元素

    int value_Y = 0; // 用于存储延长后的y坐标
    // 存储延长后的线段坐标
    std::vector<int16_t> extended_line(4);
    // 处理垂直线情况 (x1 == x2)
    if (x1 == x2) {
        value_Y = 480+200;  // 这种情况一般不会出现，如果真的出现，说明机器人跑到黑线的正中央了，这时当做黑线在机器人偏右边处理
    }
    // 处理斜线情况
    else {
        // 计算斜率和截距
        float k = static_cast<float>(y2 - y1) / (x2 - x1);
        float b = y1 - k * x1;
        value_Y = static_cast<int>(k * 0 + b); // 计算y坐标
    }
    // ROS_INFO("Extended line coordinates: %d", value_Y);
    return value_Y; 
}

// 获取循迹数据
void ProcessDataNode::trackdata_Callback(const tracking_pkg::track::ConstPtr& track_msg)
{
    // Test
    // extend_Y = extendLineCoordinates(track_msg);
    // ROS_INFO("Extended line coordinates: %d", extend_Y);

    if (current_state == RobotState::INTERIM) {            // 过渡状态
        if (encoder_diatance >= INTERIM_distance) {  // 退出来需要的距离阈值
            extend_Y = extendLineCoordinates(track_msg);
            if (extend_Y >= 200)  // 根据实际情况调整
            {
                current_state = RobotState::TRANSPORT;  // 切换到运输状态
                return;
            }
            
            PWM PWM_Motor = calculatePWM(yaw_angle, 90.0f);     
            serial_msg.PWM_Left = PWM_Motor.PWM_Left;
            serial_msg.PWM_Right = PWM_Motor.PWM_Right;
            serial_msg.command = COMMAND_COMMON;  // 正常状态
            serial_data_pub.publish(serial_msg);
            ros::Duration(0.1).sleep();  // 等待一段时间，模拟控制
        } else {
            PWM PWM_Motor = calculatePWM(yaw_angle, 0.0f);   // 目标角度为0.0    
            serial_msg.PWM_Left = PWM_Motor.PWM_Left;
            serial_msg.PWM_Right = PWM_Motor.PWM_Right;
            serial_msg.command = COMMAND_COMMON;
            serial_data_pub.publish(serial_msg);
        } 
    } else if (current_state == RobotState::TRANSPORT) {            // 运输状态
        extend_Y = extendLineCoordinates(track_msg);
        // PWM PWM_Motor = calculatePWM(yaw_angle, extend_Y, 180.0, 480); 
        PWM PWM_Motor = calculatePWM(yaw_angle, 480, 180.0, 480);    
        serial_msg.PWM_Left = PWM_Motor.PWM_Left;
        serial_msg.PWM_Right = PWM_Motor.PWM_Right;
        ROS_INFO("extend_Y: %d PWM_Motor:%d, %d", extend_Y, PWM_Motor.PWM_Left, PWM_Motor.PWM_Right);
        serial_msg.command = 15;
        serial_data_pub.publish(serial_msg);
    }
}

// 获取相机数据
void ProcessDataNode::cameradata_Callback(const yolo11_pkg::array::ConstPtr& camera_msg)
{
    tmp_camera_points.clear();
    for(const auto& camera_data: camera_msg->array){
        float x = camera_data.x;
        float y = camera_data.y;
        float r = std::sqrt(x * x + y * y);          // 计算半径
        float theta_rad = std::atan2(y, x);          // 计算角度（弧度）
        // ROS_INFO("Received camera:%.3f,%.3f",r,theta_rad);
        // ROS_INFO("Received xycamera:%.3f,%.3f",x,y);

        tmp_camera_points.emplace_back(x,y);
    }
}

// 获取雷达数据，并与相机数据做数据关联与融合
void ProcessDataNode::radardata_Callback(const radar_msgs::array::ConstPtr& radar_msg)
{
    for(const auto& radar_data: radar_msg->array){
        float x = -radar_data.r * 100 * std::sin(radar_data.phi);  // 计算x坐标
        float y = radar_data.r * 100 * std::cos(radar_data.phi);  // 计算y坐标
        // ROS_INFO("Received radar:%.3f,%.3f",radar_data.r,radar_data.phi);
        // ROS_INFO("Received xyradar:%.3f,%.3f",x,y);

        radar_points.emplace_back(x,y);
    }
    camera_points = tmp_camera_points;
    // ROS_INFO("Matchs:%lu ,%lu",camera_points.size(),radar_points.size());
    if(camera_points.size() > 0 && radar_points.size() > 0) {
        // 进行数据关联
        auto matched_pairs = associatePoints(radar_points, camera_points, 10);  // 最大匹配距离为10

        for (const auto& pair : matched_pairs) {
            camera_matchs.emplace_back(pair.first.toVector2d());
            radar_matchs.emplace_back(pair.second.toVector2d());
        }
        //将雷达数据与相机数据进行融合
        fused_matchs = fuser.fusePositions(camera_matchs, radar_matchs);
        // for (auto match:fused_matchs)
        // {
        //     ROS_INFO("fused_matchs:%.3f,%.3f",match[0],match[1]);
        // }
        
        // 得到所有花盆的融合坐标后，这里有两种情况：
        // 1，如果当前状态是抓取状态，则选择最近的花盆作为目标位置
        // 2，如果当前状态是摆放状态，则通过所有花盆位置推算出新花盆应该摆放的位置
        // 3，如果当前状态是过渡、运输和返回状态，则不识别花盆位置
        if (current_state == RobotState::GRASP) {
            // 选择最近的花盆
            Point target_pot = selectClosestPot(convert(fused_matchs));
            
            // 卡尔曼滤波处理
            kf.Kalman_process(target_pot);
            // // 获取滤波后的目标位置（相对于机器人）
            Eigen::Vector2d filtered_pos = kf.getPosition();
            PWM PWM_Motor = calculatePWM(filtered_pos);
            serial_msg.PWM_Left = PWM_Motor.PWM_Left;
            serial_msg.PWM_Right = PWM_Motor.PWM_Right;
            if (filtered_pos.y() < 20.0) {  // 如果y坐标小于20，说明花盆已经接近机器人
                serial_msg.command = COMMAND_GRASP;  // 发送抓取指令
                // 延时
                ros::Duration(3.0).sleep();  // 等待3s，等待机械臂抓取完成
                current_state = RobotState::INTERIM;  // 切换到过渡状态
                serial_msg.clear_encoder = true; // 发送清除编码器数据的标志
            } else{
                serial_msg.command = COMMAND_COMMON;   // 正常状态
            }
            serial_data_pub.publish(serial_msg);
            // ROS_INFO("PWM_Motor:%d,%d", PWM_Motor.PWM_Left, PWM_Motor.PWM_Right);
            // ROS_INFO("Fused data:%.3f,%.3f",filtered_pos[0],filtered_pos[1]);
        } else if (current_state == RobotState::ARRANGE) {            // 摆放状态
            // 待实现

        } else {      // 返回状态
            // 不处理花盆位置
            return;
        }
        
            
    }
    camera_points.clear();
    radar_points.clear();
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "processdata_node");
    ProcessDataNode pcsdnode;
    ros::spin();
    return 0;
}
