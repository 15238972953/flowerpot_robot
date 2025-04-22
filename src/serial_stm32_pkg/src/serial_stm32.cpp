#include "serial_stm32.h"
#include <iostream>

// rosrun serial_stm32_pkg serial_stm32 _port:=/dev/ttyTHS0 _baud_rate:=115200
SerialCommNode::SerialCommNode() {
    // 从参数服务器获取串口配置参数
    ros::NodeHandle private_nh("~");
    private_nh.param<std::string>("port", port_, "/dev/ttyTHS0");
    private_nh.param("baud_rate", baud_rate_, 115200);
    
    // 订阅serial_data话题，用于接收要发送给STM32的数据
    serial_data_sub_ = nh_.subscribe<processdata_pkg::serial_data>(
        "serial_data", 100, &SerialCommNode::serialDataCallback, this);
    
    // 初始化串口
    if (!setupSerialPort()) {
        ROS_ERROR("Failed to initialize serial port!");
        ros::shutdown();
    }
}

SerialCommNode::~SerialCommNode() {
    if (serial_.isOpen()) {
        serial_.close();
    }
}

bool SerialCommNode::setupSerialPort() {
    try {
        serial_.setPort(port_);
        serial_.setBaudrate(baud_rate_);
        serial::Timeout timeout = serial::Timeout::simpleTimeout(1000);
        serial_.setTimeout(timeout);
        serial_.open();
        
        if (!serial_.isOpen()) {
            ROS_ERROR("Serial port %s could not be opened.", port_.c_str());
            return false;
        }
        
        ROS_INFO("Serial port %s opened successfully at %d baud.", 
                port_.c_str(), baud_rate_);
        return true;
    } catch (serial::IOException& e) {
        ROS_ERROR("Serial port exception: %s", e.what());
        return false;
    }
}

void SerialCommNode::serialDataCallback(const processdata_pkg::serial_data::ConstPtr& msg) {
    ROS_INFO("Hello");
    if (!serial_.isOpen()) {
        ROS_WARN("Serial port is not open. Cannot send data.");
        return;
    }
    try {
        // 发送数据到STM32
        std::vector<uint8_t> buffer(3);
        buffer.push_back(msg->PWM_Left);
        buffer.push_back(msg->PWM_Right);
        buffer.push_back(msg->command);
        size_t bytes_written = serial_.write(buffer);

        ROS_DEBUG("Sent %lu bytes to STM32", bytes_written);
    } catch (serial::IOException& e) {
        ROS_ERROR("Error writing to serial port: %s", e.what());
    }
}

//CRC校验：CRC4多项式 x^4 + x + 1 (0x3)
// uint8_t calculateCRC4(uint8_t byte1, uint8_t byte2, uint8_t byte3_high) {
//     uint8_t crc = 0xF;
//     uint32_t data = (byte1 << 16) | (byte2 << 8) | byte3_high;
    
//     for(int i = 23; i >= 0; i--) {
//         crc ^= (data >> i) & 0x1;
//         if(crc & 0x8) {
//             crc = (crc << 1) ^ 0x3;
//         } else {
//             crc <<= 1;
//         }
//         crc &= 0xF;
//     }
//     return crc;
// }

// // 打包数据
// void packData(uint16_t data, uint8_t& byte1, uint8_t& byte2, uint8_t& byte3) {
//     byte1 = (data >> 12) & 0xFF;
//     byte2 = (data >> 4) & 0xFF;
//     uint8_t byte3_high = (data & 0x0F) << 4;
//     uint8_t checksum = calculateNibbleChecksum(byte1, byte2, byte3_high);
//     byte3 = byte3_high | checksum;
// }

// // 解包并校验
// bool unpackAndVerify(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint16_t& out_data) {
//     uint8_t received_checksum = byte3 & 0x0F;
//     uint8_t byte3_high = byte3 & 0xF0;
//     uint8_t calculated_checksum = calculateNibbleChecksum(byte1, byte2, byte3_high);
    
//     if(received_checksum == calculated_checksum) {
//         out_data = (byte1 << 12) | (byte2 << 4) | (byte3_high >> 4);
//         return true;
//     }
//     return false;
// }

// void SerialCommNode::run() {
//     ros::Rate loop_rate(12); // 12Hz
    
//     while (ros::ok()) {
//         // 处理ROS回调
//         ros::spinOnce();
//         loop_rate.sleep();
//     }
// }

int main(int argc, char** argv) {
    ros::init(argc, argv, "serial_stm32_node");
    
    SerialCommNode node;
    // node.run();
    ros::spin();
    return 0;
}