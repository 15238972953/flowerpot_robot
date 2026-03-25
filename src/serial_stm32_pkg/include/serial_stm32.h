#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <ros/ros.h>
#include <serial/serial.h>
#include <common_msgs_pkg/serial_data.h>
#include <vector>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_datatypes.h>
#include <common_msgs_pkg/encoder.h>
#include <std_msgs/Bool.h>

// #define FRAME_SIZE 10
#define FRAME_SIZE 11     // 11字节：增加一个记录GPS信息的标志位
#define HEADER_BYTE 0x55

#define ONLY_ENCODER 1

#define RECORD_GPS 0x04   // STM32发送的标志位，表示是否记录GPS信息
#define IF_GRASPED 0x02   // STM32发送的标志位，表示是否完成抓取
#define IF_RELEASED 0x01  // STM32发送的标志位，表示是否完成释放

class SerialCommNode {
public:
    SerialCommNode();
    ~SerialCommNode();
    
    // 接收stm32端传来的编码器数据
    void ReceiveData();

    // 更新里程计信息
    void updateOdometry();

private:
    void serialDataCallback(const common_msgs_pkg::serial_data::ConstPtr& msg);
    bool setupSerialPort();
    
    ros::NodeHandle nh_;
    ros::Subscriber serial_data_sub_;   // 订阅serial_data话题
    #ifdef ONLY_ENCODER
        ros::Publisher encoder_pub_; // 发布编码器数据
        ros::Publisher grasped_pub;  // 发布抓取完成标志位
        ros::Publisher released_pub; // 发布释放完成标志位
        common_msgs_pkg::encoder encoder_msg; // 编码器数据
    #else
        ros::Publisher odom_pub_;    // 发布标准里程计
        nav_msgs::Odometry odom;
    #endif

    serial::Serial serial_;
    std::string port_;
    int baud_rate_; 
    double left_speed_ = 0.0;      // 左轮线速度(m/s)
    double right_speed_ = 0.0;     // 右轮线速度(m/s)
    double x_ = 0.0, y_ = 0.0;     // 位置(m)
    double theta_ = 0.0;           // 方向(rad)
    double wheel_separation_ = 0.355;      // 轮间距(m)
    double wheel_radius_ = 0.09;          // 轮半径(m)
    ros::Time last_time_ = ros::Time::now();

    bool _clear_encoder = false; // 是否清除编码器数据

    static int8_t is_recorded; // 是否完成一次记录
    std_msgs::Bool grasped_msg; // 发布抓取完成标志位
    std_msgs::Bool released_msg; // 发布释放完成标志位
};
// uint8_t calculateCRC4(uint8_t byte1, uint8_t byte2, uint8_t byte3_high);
// void packData(uint16_t data, uint8_t& byte1, uint8_t& byte2, uint8_t& byte3);

#endif // SERIAL_COMM_H