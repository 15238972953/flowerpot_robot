#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <ros/ros.h>
#include <serial/serial.h>
#include <processdata_pkg/serial_data.h>
#include <serial_stm32_pkg/EncoderData.h>
#include <vector>

#define FRAME_SIZE 10
#define HEADER_BYTE 0x55

class SerialCommNode {
public:
    SerialCommNode();
    ~SerialCommNode();
    
    void ReceiveData();

private:
    void serialDataCallback(const processdata_pkg::serial_data::ConstPtr& msg);
    bool setupSerialPort();
    
    ros::NodeHandle nh_;
    ros::Subscriber serial_data_sub_;   // 订阅serial_data话题
    ros::Publisher encoder_data_pub_;   // 发布编码器数据到EncoderData话题
    
    serial::Serial serial_;
    std::string port_;
    int baud_rate_;
    serial_stm32_pkg::EncoderData encoder_data_msg_; // 用于发布的消息类型
};

// uint8_t calculateCRC4(uint8_t byte1, uint8_t byte2, uint8_t byte3_high);
// void packData(uint16_t data, uint8_t& byte1, uint8_t& byte2, uint8_t& byte3);

#endif // SERIAL_COMM_H