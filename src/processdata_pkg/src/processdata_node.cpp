#include "processdata_node.h"

// yolo11_pkg::array::Ptr camera_msg;

ProcessDataNode::ProcessDataNode() {
    // 初始化订阅者
    radar_processed_sub = nh.subscribe("Array_Radar", 1000, &ProcessDataNode::radarCallback, this);
    camera_processed_sub = nh.subscribe("yolo11_data", 1000, &ProcessDataNode::cameraCallback, this);
}

void ProcessDataNode::cameradata_Callback(const yolo11_pkg::array::ConstPtr& camera_msg)
{
    // camera_msg.reset(new yolo11_pkg::array(*camera_msg));   //将信息转存到全局变量camera_msg中

    for(const auto& camera_data: camera_msg->array){
        int x = static_cast<int>(camera_data.x);
        int y = static_cast<int>(camera_data.y);
        float r = std::sqrt(x * x + y * y);          // 计算半径
        float theta_rad = std::atan2(y, x);          // 计算角度（弧度）
        ROS_INFO("Received camera:%.3f,%.3f",r,theta_rad);
        // ROS_INFO("Received camera:%d,%d",x,y);

        camera_points.emplace_back(r,theta_rad);
    }
}

// 获取雷达数据，并与相机数据做数据关联与融合
void ProcessDataNode::radardata_Callback(const radar_msgs::array::ConstPtr& radar_msg)
{
    for(const auto& radar_data: radar_msg->array){
        int x = radar_data.r * std::cos(radar_data.phi);  // 计算x坐标
        int y = radar_data.r * std::sin(radar_data.phi);  // 计算y坐标
        ROS_INFO("Received radar:%.3f,%.3f",radar_data.r,radar_data.phi);
        // ROS_INFO("Received radar:%d,%d",x,y);

        radar_points.emplace_back(radar_data.r,radar_data.phi);
    }
    
    if(camera_points.size() > 0 && radar_points.size() > 0){
        // 进行数据关联
        auto association = associatePoints(radar_points, camera_points);
        // 进行数据融合
        for(const auto& pair: association){
            int radar_index = pair.first;
            int camera_index = pair.second;
            if(camera_index != -1){
                //将雷达数据与相机数据进行融合
            }
        }
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "processdata_node");
    ros::spin();
    return 0;
}
