#include "serial_stm32.h"
#include <iostream>

int8_t SerialCommNode::is_recorded = 0x00; // 初始化为0x00，表示默认未完成一次记录

// rosrun serial_stm32_pkg serial_stm32_node _port:=/dev/ttyTHS0 _baud_rate:=115200
SerialCommNode::SerialCommNode() {
    // 从参数服务器获取串口配置参数
    ros::NodeHandle private_nh("~");
    private_nh.param<std::string>("port", port_, "/dev/ttyTHS0");
    private_nh.param("baud_rate", baud_rate_, 115200);
    
    // 订阅serial_data话题，用于接收要发送给STM32的数据
    serial_data_sub_ = nh_.subscribe<common_msgs_pkg::serial_data>(
        "serial_data", 100, &SerialCommNode::serialDataCallback, this);
    
    // 发布标准里程计
    #ifdef ONLY_ENCODER
        encoder_pub_ = nh_.advertise<common_msgs_pkg::encoder>("encoder_msg", 50);
        grasped_pub = nh_.advertise<std_msgs::Bool>("grasped_status", 10);
        released_pub = nh_.advertise<std_msgs::Bool>("released_status", 10);
    #else
        odom_pub_ = nh_.advertise<nav_msgs::Odometry>("wheel_odom", 50);
    #endif
    
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

// 累加和校验
uint8_t SerialCommNode::calculateChecksum(const std::vector<uint8_t>& data) {
    uint8_t sum = 0;
    for (size_t i = 0; i < data.size() - 1; ++i) { // 最后一个字节是校验位，不参与计算
        sum += data[i];
    }
    return sum;
}

void SerialCommNode::serialDataCallback(const common_msgs_pkg::serial_data::ConstPtr& msg) {
    // _clear_encoder = msg->clear_encoder; // 获取是否清除编码器数据的标志
    // ROS_INFO("Hello");
    if (!serial_.isOpen()) {
        ROS_INFO("Serial port is not open. Cannot send data.");
        return;
    }
    try {
        // 发送数据到STM32
        std::vector<uint8_t> buffer(5);
        buffer[0] = HEADER_BYTE; // 帧头
        buffer[1] = msg->PWM_Left;
        buffer[2] = msg->PWM_Right;
        buffer[3] = msg->command;  
        buffer[4] = calculateChecksum(buffer); // 填充最后一个字节，确保数据长度正确

        size_t bytes_written = serial_.write(buffer);
        for(int i=0;i<buffer.size();++i){
            ROS_INFO("buffer:%d,%d",i,buffer[i]);
        }
        ROS_INFO("Sent %lu bytes to STM32", bytes_written);
    } catch (serial::IOException& e) {
        ROS_INFO("Error writing to serial port: %s", e.what());
    }
}

// 更新里程计信息,编码器发布的应该是速度信息
void SerialCommNode::updateOdometry() {
    #ifdef ONLY_ENCODER
        // if (_clear_encoder) {
        //     encoder_msg.left_distance = 0.0;
        //     encoder_msg.right_distance = 0.0;
        //     _clear_encoder = false; // 重置清除标志
        // }
        
        // // 计算时间间隔
        // ros::Time current_time = ros::Time::now();
        // float dt = (current_time - last_time_).toSec();
        // last_time_ = current_time;

        // // 分别计算左右轮的运动距离
        // float right_distance = right_speed_ * dt; 
        // float left_distance = left_speed_ * dt;

        // encoder_msg.right_distance += right_distance;
        // encoder_msg.left_distance += left_distance;
        // encoder_pub_.publish(encoder_msg);
        encoder_msg.right_speed = right_speed_;
        encoder_msg.left_speed = left_speed_;
        encoder_pub_.publish(encoder_msg);
    #else
        // 计算时间间隔
        ros::Time current_time = ros::Time::now();
        double dt = (current_time - last_time_).toSec();
        last_time_ = current_time;

        // 计算线速度和角速度（差分驱动模型）
        double linear_vel = (right_speed_ + left_speed_) / 2.0;
        double angular_vel = (right_speed_ - left_speed_) / wheel_separation_;

        // 更新位置和方向（航迹推算）
        theta_ += angular_vel * dt;
        x_ += linear_vel * cos(theta_) * dt;
        y_ += linear_vel * sin(theta_) * dt;

        // 填充Odometry消息
        odom.header.stamp = current_time;
        odom.header.frame_id = "odom";
        odom.child_frame_id = "base_link";

        // 位置
        odom.pose.pose.position.x = x_;
        odom.pose.pose.position.y = y_;
        odom.pose.pose.position.z = 0.0;
        odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(theta_);

        // 速度
        odom.twist.twist.linear.x = linear_vel;
        odom.twist.twist.angular.z = angular_vel;

        // 发布里程计
        odom_pub_.publish(odom);

        // 打印调试信息（可选）
        // ROS_DEBUG_THROTTLE(1.0, "Odom - x: %.2f m, y: %.2f m, theta: %.2f rad", x_, y_, theta_);
    #endif
}


void SerialCommNode::ReceiveData() {
        ros::Rate rate(10); // 10Hz
        uint8_t buffer[FRAME_SIZE];
        size_t bytes_read = 0;
        
        while (ros::ok()) {
            // 清空缓冲区并尝试读取
            serial_.flushInput();
            // 尝试读取一帧数据
            try {
                bytes_read = serial_.read(buffer, FRAME_SIZE);
            } catch (serial::IOException& e) {
                ROS_ERROR_STREAM("Serial read error: " << e.what());
                continue;
            }
            
            // 检查是否收到完整帧
            if (bytes_read == FRAME_SIZE) {
                // 打印接收数据
                // std::stringstream ss;
                // ss << "Received bytes:";
                // for (int i = 0; i < FRAME_SIZE; ++i) {
                //     ss << " 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]);
                // }
                // ROS_INFO("%s", ss.str().c_str());
                // int32_t data1 = *reinterpret_cast<int32_t*>(&buffer[1]);
                // ROS_INFO("Left  Speed: %.4f m/s", static_cast<float>(data1/10000.0));
                // int32_t data2 = *reinterpret_cast<int32_t*>(&buffer[5]);
                // ROS_INFO("right Speed: %.4f m/s", static_cast<float>(data2/10000.0));

                // 验证帧头
                if (buffer[0] == HEADER_BYTE) {
                    // 计算校验和
                    uint8_t checksum = 0;
                    for (int i = 0; i < FRAME_SIZE - 1; i++) {
                        checksum += buffer[i];
                    }
                    // 验证校验和
                    if (checksum == buffer[FRAME_SIZE - 1]) {
                        // 解析数据
                        int8_t data1 = buffer[1];
                        left_speed_ = data1;
                        int8_t data2 = buffer[2];
                        right_speed_ = data2;
                        updateOdometry();

                        // GPS记录标志位参数服务器更新
                        if(buffer[3] & RECORD_GPS) {
                            nh_.setParam("/robot/gps_flag", true);   // 设置GPS标志位为true，表示可以记录GPS信息
                        }else {
                            nh_.setParam("/robot/gps_flag", false);  // 设置GPS标志位为false，表示不记录GPS信息
                        }

                        // 抓取完成标志位话题发布
                        if(buffer[3] & IF_GRASPED) {
                            grasped_msg.data = true;
                        } else {
                            grasped_msg.data = false;
                        }
                        grasped_pub.publish(grasped_msg);

                        // 释放完成标志位话题发布
                        if(buffer[3] & IF_RELEASED) {
                            released_msg.data = true;
                        }else{
                            released_msg.data = false;
                        }
                        released_pub.publish(released_msg);

                        // ROS_INFO("Received data: Encoder_Left=%f, Encoder_Right=%f", 
                        //         left_speed_, right_speed_);
                    } else {
                        ROS_WARN("Checksum error: expected 0x%02X, got 0x%02X", 
                                checksum, buffer[FRAME_SIZE - 1]);
                    }
                } else {
                    ROS_WARN("Invalid header: 0x%02X (expected 0x%02X)", 
                            buffer[0], HEADER_BYTE);
                }
            } else if (bytes_read > 0) {
                ROS_WARN("Incomplete frame: received %zu bytes (expected %d)", 
                        bytes_read, FRAME_SIZE);
            }
            
            ros::spinOnce();
            rate.sleep();
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
    node.ReceiveData();
    return 0;
}