#include "processdata_node.h"

ProcessDataNode::ProcessDataNode() {
    // 初始化订阅者
    radar_processed_sub = nh.subscribe("Array_Radar", 1000, &ProcessDataNode::radardata_Callback, this);
    camera_processed_sub = nh.subscribe("yolo11_data", 1000, &ProcessDataNode::cameradata_Callback, this);
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
        ROS_INFO("Received xycamera:%.3f,%.3f",x,y);

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
        ROS_INFO("Received xyradar:%.3f,%.3f",x,y);

        radar_points.emplace_back(x,y);
    }
    camera_points = tmp_camera_points;
    ROS_INFO("Matchs:%lu ,%lu",camera_points.size(),radar_points.size());
    if(camera_points.size() > 0 && radar_points.size() > 0){
        // 进行数据关联
        auto matched_pairs = associatePoints(radar_points, camera_points, 10);  // 最大匹配距离为10

        for (const auto& pair : matched_pairs) {
            camera_matchs.emplace_back(pair.first);
            radar_matchs.emplace_back(pair.second);
        }
        //将雷达数据与相机数据进行融合
        fused_matchs = fuser.fusePositions(camera_matchs, radar_matchs);
        
        
        ROS_INFO("Fused data:%.3f,%.3f",fused_pos[0],fused_pos[1]);
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
