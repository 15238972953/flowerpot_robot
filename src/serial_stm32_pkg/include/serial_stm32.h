#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <ros/ros.h>
#include <serial/serial.h>
#include <processdata_pkg/serial_data.h>
#include <vector>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_datatypes.h>

#define FRAME_SIZE 10
#define HEADER_BYTE 0x55

class SerialCommNode {
public:
    SerialCommNode();
    ~SerialCommNode();
    
    // 接收stm32端传来的编码器数据
    void ReceiveData();

    // 更新里程计信息
    void updateOdometry();

private:
    void serialDataCallback(const processdata_pkg::serial_data::ConstPtr& msg);
    bool setupSerialPort();
    
    ros::NodeHandle nh_;
    ros::Subscriber serial_data_sub_;   // 订阅serial_data话题
    ros::Publisher odom_pub_;           

    serial::Serial serial_;
    std::string port_;
    int baud_rate_;
    nav_msgs::Odometry odom; 
    double left_speed_ = 0.0;      // 左轮线速度(m/s)
    double right_speed_ = 0.0;     // 右轮线速度(m/s)
    double x_ = 0.0, y_ = 0.0;     // 位置(m)
    double theta_ = 0.0;           // 方向(rad)
    double wheel_separation_ = 0.355;      // 轮间距(m)
    double wheel_radius_ = 0.09;          // 轮半径(m)
    ros::Time last_time_ = ros::Time::now();
        
};

// uint8_t calculateCRC4(uint8_t byte1, uint8_t byte2, uint8_t byte3_high);
// void packData(uint16_t data, uint8_t& byte1, uint8_t& byte2, uint8_t& byte3);

#endif // SERIAL_COMM_H