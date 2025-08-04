#include "imu_node.h"
#include <boost/circular_buffer.hpp>
#include <cstdint>

ReadState current_state = ReadState::WAIT_FOR_55;

SerialReader::SerialReader(ros::NodeHandle& nh) : nh_(nh), private_nh_("~"), is_serial_connected_(false) {
    // 初始化 Publisher，话题名称为 "yaw_angle"
    yaw_pub_ = nh.advertise<std_msgs::Float32>("yaw_angle", 10);
    // 从参数服务器获取配置
    private_nh_.param<std::string>("port", port_, "/dev/ttyUSB0");
    private_nh_.param<int>("baudrate", baudrate_, 9600);
    
    // 初始化串口
    is_serial_connected_ = initSerial();
}

SerialReader::~SerialReader() {
    if (serial_.isOpen()) {
        serial_.close();
        ROS_INFO("Serial port closed");
    }
}

bool SerialReader::initSerial() {
    try {
        serial_.setPort(port_);
        serial_.setBaudrate(baudrate_);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        serial_.setTimeout(to);
        serial_.open();
        
        if (serial_.isOpen()) {
            ROS_INFO_STREAM("Serial port: " << port_ << " is opened, baudrate= " << baudrate_);
            return true;
        }
    } catch (const serial::IOException& e) {
        ROS_ERROR_STREAM("cannot open Serial port: " << port_ << ": " << e.what());
    } catch (const std::exception& e) {
        ROS_ERROR_STREAM("Serial port initialization error! " << e.what());
    }
    
    return false;
}

void SerialReader::processData(const std::vector<uint8_t> &frame) {
    // 检查包头
    if (frame[0] == FRAME_HEADER && frame[11] == FRAME_HEADER && frame[22] == FRAME_HEADER && frame[33] == FRAME_HEADER) {

        // 角度数据说明：
        //   1   2     3     4     5       6    7     8  9  10 11
        // 0x55	0x53 RollL RollH PitchL	PitchH YawL	YawH VL	VH SUM

        if(frame[10] == static_cast<uint8_t>(frame[0] + frame[1] + frame[2] + frame[3] + frame[4] + 
                        frame[5] + frame[6] + frame[7] + frame[8] + frame[9])) {
            float yaw = static_cast<float>(((frame[7]<<8)|frame[6])/32768.0f*180.0f);
            ROS_INFO("Now Angle - Yaw: %.2f", yaw);
             // 发布 yaw 数据
            std_msgs::Float32 yaw_msg;
            yaw_msg.data = yaw;
            yaw_pub_.publish(yaw_msg);
        } else {
            ROS_ERROR("Checksum error, data may be corrupted");
        }
    }
}

void SerialReader::readData() {
    std::vector<uint8_t> temp(44);
    while (serial_.available() > 0) {
        uint8_t byte;
        if (current_state == ReadState::WAIT_FOR_55) {
            size_t bytes_read = serial_.read(&byte, 1);  // 每次读取 1 字节
            if (bytes_read == 1 && byte == 0x55) {
                size_t bytes_read = serial_.read(&byte, 1);
                if (bytes_read == 1 && byte == 0x52) {
                    ROS_INFO("Received frame header 0x55 0x52, preparing to read 44 bytes");
                    uint8_t discard_buffer[9];  // 临时缓冲区（不存储，仅用于读取）
                    size_t bytes_read = serial_.read(discard_buffer, sizeof(discard_buffer));  // 读取 9 字节
                    current_state = ReadState::READ_44_BYTES;
                }                    
            }    
        } else {
            size_t bytes_read = serial_.read(temp.data(), 44);
            if (bytes_read == 44) {
                // 以十六进制打印数据，每行11个
                // for (size_t i = 0; i < temp.size(); i += 11) {
                //     std::stringstream ss;
                //     ss << "Data [" << i << "-" << std::min(i+10, temp.size()-1) << "]: ";
                //     for (size_t j = i; j < i+11 && j < temp.size(); j++) {
                //         ss << "0x" << std::hex << std::setw(2) << std::setfill('0') 
                //         << static_cast<int>(temp[j]) << " ";
                //     }
                //     ROS_INFO("%s", ss.str().c_str());
                // }
                // 处理读取到的数据
                processData(temp);
            } else {
                ROS_WARN("Expected 44 bytes");
            }  
        }
    }
}

void SerialReader::run() {
    if (!is_serial_connected_) {
        ROS_ERROR("Serial port not connected, cannot run");
        return;
    }
    ROS_DEBUG_STREAM("Serial port connected");
    ros::Rate loop_rate(10); // 50Hz
    while (ros::ok() && is_serial_connected_) {
        // ROS_INFO("Reading data from serial port...");
        try {
            readData(); // 确保内部有超时逻辑
        } catch (const std::exception& e) {
            ROS_ERROR("Read failed: %s", e.what());
        }
        loop_rate.sleep();
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "imu_node");
    ros::NodeHandle nh;
    
    SerialReader reader(nh);
    ROS_INFO("Serial port connected");
    reader.run();
    return 0;
}