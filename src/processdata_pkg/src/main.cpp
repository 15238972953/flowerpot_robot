#include "processdata_node.h"
#define ONLY_CAMERA 1   // 如果只使用相机识别，不使用融合

void ProcessDataNode::run() {
    ros::Rate rate(10);
    while (ros::ok()) {
        ros::spinOnce();

        #if ONLY_CAMERA==1
            if(camera_points.size() > 0) {
                target_pot = selectClosestPot(camera_points);
            }

        #else
            if(camera_points.size() > 0 && radar_points.size() > 0) {
                // 进行数据关联
                auto matched_pairs = associatePoints(radar_points, camera_points, 10);  // 最大匹配距离为10

                for (const auto& pair : matched_pairs) {
                    camera_matchs.emplace_back(pair.first.toVector2d());
                    radar_matchs.emplace_back(pair.second.toVector2d());
                    ROS_INFO("Received xyradar:%.3f,%.3f",pair.second.x,pair.second.y);
                }
                ROS_INFO("size:%d,%d",matched_pairs.size(), radar_matchs.size());
                //将雷达数据与相机数据进行融合
                fused_matchs = fuser.fusePositions(camera_matchs, radar_matchs);
                target_pot = selectClosestPot(convert(fused_matchs));
                // kf.Kalman_process(target_pot);
                ROS_INFO("target_pot:x = %.3f, y = %.3f",target_pot.x, target_pot.y);

                radar_matchs.clear();
            }
        #endif

        // 发布topic
        std_msgs::Float64MultiArray pot_coords_msg;
        pot_coords_msg.data.push_back(target_pot.x);
        pot_coords_msg.data.push_back(target_pot.y);
        pot_coords_pub.publish(pot_coords_msg);

        camera_matchs.clear();
        
        

        rate.sleep();
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "processdata_node");
    ProcessDataNode pcsdnode;
    pcsdnode.run();
    return 0;
}
