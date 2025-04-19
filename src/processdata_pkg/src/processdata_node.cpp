#include<ros/ros.h>
#include<radar_msgs/array.h>
#include<radar_msgs/radar.h>
#include<yolo11_pkg/coordinate.h>
#include<yolo11_pkg/array.h>

yolo11_pkg::array::Ptr camera_msg;

void cameradata_Callback(const yolo11_pkg::array::ConstPtr& msg)
{
    camera_msg.reset(new yolo11_pkg::array(*msg));
    // for(const auto& camera_data: msg->array){
    //     ROS_INFO("Received camera:%d,%d",static_cast<int>(camera_data.x),static_cast<int>(camera_data.y));
    // }
}
void processdata_Callback(const radar_msgs::array::ConstPtr& radar_msg)
{
    // 做数据关联与融合
    for(const auto& radar_data: radar_msg->array){
        for(const auto& camera_data: camera_msg->array){
            
        }
        ROS_INFO("Received radar:%d,%.3f,%.3f",static_cast<int>(radar_data.n),radar_data.r,radar_data.phi);
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "processdata_node");
    ros::NodeHandle nh;
    ros::Subscriber radar_processed_sub = nh.subscribe("Array_Radar", 1000, &processdata_Callback);
    ros::Subscriber camera_processed_sub = nh.subscribe("yolo11_data", 1000, &cameradata_Callback);
    ros::spin();
    return 0;
}
