#ifndef MY_SERIAL_COMMUNICATION_SERIAL_READER_H
#define MY_SERIAL_COMMUNICATION_SERIAL_READER_H

#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <vector>

// 帧配置（根据设备手册修改）
const uint8_t FRAME_HEADER = 0x55;       // 帧头
const size_t FRAME_LENGTH = 11;          // 固定帧长
const size_t RING_BUFFER_SIZE = 128;    // 环形缓冲区大小（建议为2的幂，优化取模运算）

// 环形缓冲区结构
struct RingBuffer {
    uint8_t data[RING_BUFFER_SIZE];
    size_t head = 0;  // 数据写入位置
    size_t tail = 0;  // 数据读取位置
    size_t count = 0; // 当前有效数据量

    // 写入数据
    size_t write(const uint8_t* src, size_t len) {
        size_t write_len = std::min(len, RING_BUFFER_SIZE - count);
        for (size_t i = 0; i < write_len; ++i) {
            data[head] = src[i];
            head = (head + 1) % RING_BUFFER_SIZE;
        }
        count += write_len;
        return write_len;
    }

    // 读取单个字节（从tail位置）
    uint8_t readByte() {
        if (count == 0) return 0;
        uint8_t byte = data[tail];
        tail = (tail + 1) % RING_BUFFER_SIZE;
        count--;
        return byte;
    }

    // 跳过指定长度数据
    void skip(size_t len) {
        size_t skip_len = std::min(len, count);
        tail = (tail + skip_len) % RING_BUFFER_SIZE;
        count -= skip_len;
    }

    // 查看指定位置的字节（不移动指针）
    uint8_t peek(size_t offset = 0) const {
        if (offset >= count) return 0;
        size_t pos = (tail + offset) % RING_BUFFER_SIZE;
        return data[pos];
    }

    // 清空缓冲区
    void clear() {
        head = tail = count = 0;
    }
};

class SerialReader {
public:
    struct SAngle{
        uint8_t roll[2];
        uint8_t pitch[2];
        uint8_t yaw[2];
        uint8_t V[2];
        uint8_t sum;
    };
    static RingBuffer ring_buf;
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
    ros::Publisher data_pub_;       // 数据发布者
    
    serial::Serial serial_;         // 串口对象
    std::string port_;              // 串口端口
    int baudrate_;                  // 波特率
    bool is_serial_connected_;      // 串口连接状态
};

#endif // MY_SERIAL_COMMUNICATION_SERIAL_READER_H