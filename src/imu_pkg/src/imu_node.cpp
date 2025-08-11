#include "imu_node.h"
#include <boost/circular_buffer.hpp>
#include <cstdint>

ReadState current_state = ReadState::WAIT_FOR_55;

SerialReader::SerialReader(ros::NodeHandle& nh) : nh_(nh), private_nh_("~"), is_serial_connected_(false) {
    // 初始化 Publisher，话题名称为 "yaw_angle"
    #ifdef ONLY_YAW
        yaw_pub_ = nh.advertise<std_msgs::Float32>("yaw_angle", 10);   // 发布 yaw 角度到 "yaw_angle" 话题
    #else
        imu_pub_ = nh.advertise<sensor_msgs::Imu>("/imu/data", 10);    // 发布 IMU 数据到 "/imu/data" 话题
    #endif
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

        // 加速度数据说明：
        //   1   2    3   4   5   6   7   8  9  10 11
        // 0x55	0x51 AxL AxH AyL AyH AzL AzH TL	TH SUM
        // 角速度数据说明：
        //   1   2    3   4   5   6   7   8   9    10   11
        // 0x55	0x52 WxL WxH WyL WyH WzL WzH VolL VolH SUM
        // 角度数据说明：
        //   1   2     3     4     5       6    7     8  9  10 11
        // 0x55	0x53 RollL RollH PitchL	PitchH YawL	YawH VL	VH SUM
        // 磁场数据说明：
        //   1   2    3   4   5   6   7   8  9  10  11
        // 0x55	0x54 HxL HxH HyL HyH HzL HzH TL TH SUM

        #ifdef ONLY_YAW
            // 原话题，只输出yaw信息
            if(frame[10] == static_cast<uint8_t>(frame[0] + frame[1] + frame[2] + frame[3] + frame[4] + 
                            frame[5] + frame[6] + frame[7] + frame[8] + frame[9])) {
                float yaw = static_cast<float>(((frame[7]<<8)|frame[6])/32768.0f*180.0f);
                // ROS_INFO("Now Angle - Yaw: %.2f", yaw);
                // 发布 yaw 数据
                std_msgs::Float32 yaw_msg;
                yaw_msg.data = yaw;
                yaw_pub_.publish(yaw_msg);
            } else {
                ROS_ERROR("Checksum error, data may be corrupted");
            }
        #else
            // 新话题
            imu.header.stamp = ros::Time::now();
            imu.header.frame_id = "imu_link";
            // 角度
            if(frame[10] == static_cast<uint8_t>(frame[0] + frame[1] + frame[2] + frame[3] + frame[4] + 
                            frame[5] + frame[6] + frame[7] + frame[8] + frame[9])) {
                float roll = static_cast<float>(((frame[3]<<8)|frame[2])/32768.0f*180.0f);
                float pitch = static_cast<float>(((frame[5]<<8)|frame[4])/32768.0f*180.0f);
                float yaw = static_cast<float>(((frame[7]<<8)|frame[6])/32768.0f*180.0f);
                tf2::Quaternion q;
                q.setRPY(roll, pitch, yaw);
                // 四元数归一化（防止非单位四元数）
                q.normalize();
                // 四元数方向
                imu.orientation.x = q.x();
                imu.orientation.y = q.y();
                imu.orientation.z = q.z();
                imu.orientation.w = q.w();

                // ROS_INFO("Quaternion - x: %f, y: %f, z: %f, w: %f", q.x(), q.y(), q.z(), q.w());
                // // 计算四元数平方和
                // double norm_sq = q.x()*q.x() + q.y()*q.y() + q.z()*q.z() + q.w()*q.w();
                // ROS_INFO("Quaternion norm squared: %.6f (expected: 1.000000)", norm_sq);
            }

            // 磁场（暂未用到）
            // if(frame[21] == static_cast<uint8_t>(frame[11] + frame[12] + frame[13] + frame[14] + frame[15] + 
            //                 frame[16] + frame[17] + frame[18] + frame[19] + frame[20])){}
            
            // 线加速度(暂时不用)
            // if(frame[32] == static_cast<uint8_t>(frame[22] + frame[23] + frame[24] + frame[25] + frame[26] + 
            //                 frame[27] + frame[28] + frame[29] + frame[30] + frame[31])) {
            //     imu.linear_acceleration.x = static_cast<float>(((frame[25]<<8)|frame[24])/32768.0f*16.0f);
            //     imu.linear_acceleration.y = static_cast<float>(((frame[27]<<8)|frame[26])/32768.0f*16.0f);
            //     imu.linear_acceleration.z = static_cast<float>(((frame[29]<<8)|frame[28])/32768.0f*16.0f);
            // }

            // 角速度
            if(frame[43] == static_cast<uint8_t>(frame[33] + frame[34] + frame[35] + frame[36] + frame[37] +
                            frame[38] + frame[39] + frame[40] + frame[41] + frame[42])) {
                imu.angular_velocity.x = static_cast<float>(((frame[36]<<8)|frame[35])/32768.0f*2000.0f);
                imu.angular_velocity.y = static_cast<float>(((frame[38]<<8)|frame[37])/32768.0f*2000.0f);
                imu.angular_velocity.z = static_cast<float>(((frame[40]<<8)|frame[39])/32768.0f*2000.0f);
            }
            
            // 设置协方差（若不知道可设为默认值）
            imu.orientation_covariance = {0.01, 0, 0, 0, 0.01, 0, 0, 0, 0.01};
            imu.angular_velocity_covariance = {0.01, 0, 0, 0, 0.01, 0, 0, 0, 0.01};
            imu.linear_acceleration_covariance = {0.01, 0, 0, 0, 0.01, 0, 0, 0, 0.01};
            
            imu_pub_.publish(imu);
        #endif
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