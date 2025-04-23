#include "processdata_node.h"
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
    //初始化发布者
    serial_data_pub = nh.advertise<processdata_pkg::serial_data>("serial_data", 1000);
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
    if(camera_points.size() > 0 && radar_points.size() > 0){
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
        
        // 选择最近的花盆
        Point target_pot = selectClosestPot(convert(fused_matchs));
        
        // 卡尔曼滤波处理
        kf.Kalman_process(target_pot);
        // // 获取滤波后的目标位置（相对于机器人）
        Eigen::Vector2d filtered_pos = kf.getPosition();
        PWM PWM_Motor = calculatePWM(filtered_pos);
        serial_msg.PWM_Left = PWM_Motor.PWM_Left;
        serial_msg.PWM_Right = PWM_Motor.PWM_Right;
        serial_msg.command = 15;
        serial_data_pub.publish(serial_msg);
        ROS_INFO("PWM_Motor:%d,%d", PWM_Motor.PWM_Left, PWM_Motor.PWM_Right);
        // ROS_INFO("Fused data:%.3f,%.3f",filtered_pos[0],filtered_pos[1]);    
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
