#ifndef MY_SERIAL_COMMUNICATION_SERIAL_READER_H
#define MY_SERIAL_COMMUNICATION_SERIAL_READER_H

#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <vector>
#include <sensor_msgs/Imu.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

enum class ReadState {
    WAIT_FOR_55,    // 等待 0x55
    READ_44_BYTES   // 读取 44 字节
};

class SerialReader {
public:
    explicit SerialReader(ros::NodeHandle& nh);

    ~SerialReader();

    void run();

private:
    /**
     * @brief 初始化串口
     * @return 初始化是否成功
     */
    bool initSerial();
    void processData(const std::vector<uint8_t> &frame);
    /**
     * @brief 读取并处理串口数据
     */
    void readData();

    ros::NodeHandle nh_;            // ROS节点句柄
    ros::NodeHandle private_nh_;    // 私有节点句柄(用于获取参数)
    ros::Publisher yaw_pub_;       // 数据发布者
    ros::Publisher imu_pub_;       // IMU数据发布者
    
    serial::Serial serial_;         // 串口对象
    std::string port_;              // 串口端口
    int baudrate_;                  // 波特率
    bool is_serial_connected_;      // 串口连接状态
    static constexpr uint8_t FRAME_HEADER = 0x55;  // 数据帧头
    sensor_msgs::Imu imu;
};

#endif // MY_SERIAL_COMMUNICATION_SERIAL_READER_H