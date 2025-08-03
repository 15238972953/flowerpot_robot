#include "imu_node.h"
#include <boost/circular_buffer.hpp>
#include <cstdint>

RingBuffer SerialReader::ring_buf; 

SerialReader::SerialReader(ros::NodeHandle& nh) 
    : nh_(nh), 
      private_nh_("~"),
      is_serial_connected_(false) {
    
    // 从参数服务器获取配置
    private_nh_.param<std::string>("port", port_, "/dev/ttyUSB0");
    private_nh_.param<int>("baudrate", baudrate_, 9600);
    
    // 初始化发布者
    data_pub_ = nh_.advertise<std_msgs::String>("serial_data", 1000);
    
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
    if (frame[0] == FRAME_HEADER && frame[1] == 0x53) {
        SAngle angle;
        memcpy(&angle, frame.data(), sizeof(SAngle));

        // 发布角度数据 (这里只发布Yaw角度)
        std_msgs::Float32 yaw_msg;
        yaw_msg.data = static_cast<float>(((angle.yaw[1]<<8)|angle.yaw[0])/32768.0f*180.0f);


        if(angle.sum == FRAME_HEADER + 0x53 + angle.roll[0] + angle.roll[1]
                    + angle.pitch[0] + angle.pitch[1] + angle.yaw[0] + angle.yaw[1]
                    + angle.V[0] + angle.V[1])
        {
            data_pub_.publish(yaw_msg);
            ROS_DEBUG_THROTTLE(1.0, "Now Angle - Yaw: %.2f", yaw_msg.data);
        }
    }
}

void SerialReader::readData() {
    // size_t available = serial_.available();
    // if (available > 0) {
    //     std::vector<uint8_t> temp(available);
    //     size_t len = serial_.read(temp.data(), available);
    //     ROS_INFO("Read %zu , cun %zu ", available, len);
    // }
    try {
        // 1. 读取数据到环形缓冲区
        size_t available = serial_.available();
        if (available > 0) {
            std::vector<uint8_t> temp(available);
            serial_.read(temp.data(), available);
            // 写入环形缓冲区（自动处理溢出）
            size_t written = ring_buf.write(temp.data(), available);
            if (written < available) {
                ROS_WARN("Ring buffer full, dropped %zu bytes", available - written);
            }
            // ROS_INFO("available: %zu , written: %zu ", available, written);
        }

        std::vector<uint8_t> frame(FRAME_LENGTH);
        // 2. 解析完整帧（利用环形缓冲区特性，避免数据拷贝）
        while (ring_buf.count >= FRAME_LENGTH) {
            ROS_INFO_STREAM("header: 0x" << std::hex << static_cast<int>(ring_buf.peek(ring_buf.tail)));
            if((frame[0]=ring_buf.readByte()) != FRAME_HEADER) {
                continue; // 重新检查缓冲区长度
            }else if((frame[1]=ring_buf.readByte()) == 0x53 && ring_buf.count >= 9){
                for (size_t i = 2; i < FRAME_LENGTH; ++i) {
                    frame[i] = ring_buf.readByte();
                }
                // 处理帧数据
                processData(frame);
            }
        }

        //     // 查找帧头（从当前tail位置开始）
        //     size_t header_offset = std::string::npos;

        //     for (size_t i = 0; i <= ring_buf.count - FRAME_LENGTH; ++i) {
        //         if (ring_buf.peek(i) == FRAME_HEADER) {
        //             header_offset = i;
        //             break;
        //         }
        //     }

        //     // // 未找到帧头：清空所有数据（快速处理）
        //     // if (header_offset == std::string::npos) {
        //     //     ring_buf.clear();
        //     //     break;
        //     // }

        //     // 跳过帧头前的无效数据
        //     if (header_offset > 0) {
        //         ring_buf.skip(header_offset);
        //         continue;  // 跳过数据后重新检查缓冲区长度
        //     }

        //     // 现在帧头位于tail位置，检查是否有完整帧
        //     if (ring_buf.count < FRAME_LENGTH) break;

        //     // 提取完整帧数据（无需拷贝，直接通过peek访问）
        //     uint8_t frame[FRAME_LENGTH];
        //     for (size_t i = 0; i < FRAME_LENGTH; ++i) {
        //         frame[i] = ring_buf.peek(i);
        //     }

        //     // 处理帧数据
        //     processData(frame);

        //     // 跳过已处理的帧（仅移动指针，无数据拷贝）
        //     ring_buf.skip(FRAME_LENGTH);
        // }

    } catch (const std::exception& e) {
        ROS_ERROR("Serial read error: %s", e.what());
        ring_buf.clear();  // 出错时清空缓冲区
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