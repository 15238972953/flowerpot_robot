#include "imu_node.h"

#define FRAME_HEADER 0x55

SerialReader::SerialReader(ros::NodeHandle& nh)
    : nh_(nh), private_nh_("~"), is_serial_connected_(false)
{
#ifdef ONLY_YAW
    yaw_pub_ = nh.advertise<std_msgs::Float32>("yaw_angle", 10);
#else
    imu_pub_ = nh.advertise<sensor_msgs::Imu>("/imu/data", 10);
#endif

    private_nh_.param<std::string>("port", port_, "/dev/ttyUSB0");
    private_nh_.param<int>("baudrate", baudrate_, 9600);

    is_serial_connected_ = initSerial();
}

SerialReader::~SerialReader()
{
    if (serial_.isOpen()) {
        serial_.close();
        ROS_INFO("Serial port closed");
    }
}

bool SerialReader::initSerial()
{
    try {
        serial_.setPort(port_);
        serial_.setBaudrate(baudrate_);
        serial::Timeout to = serial::Timeout::simpleTimeout(50);  // ⭐降低阻塞
        serial_.setTimeout(to);
        serial_.open();

        if (serial_.isOpen()) {
            ROS_INFO_STREAM("Serial port opened: " << port_);
            return true;
        }
    } catch (std::exception& e) {
        ROS_ERROR_STREAM("Serial init failed: " << e.what());
    }
    return false;
}

/// ✅ 校验函数
bool checkSum(const std::vector<uint8_t>& frame)
{
    uint8_t sum = 0;
    for (int i = 0; i < 10; i++)
        sum += frame[i];
    return sum == frame[10];
}

/// ✅ 解析单帧（11字节）
void SerialReader::parseFrame(const std::vector<uint8_t>& frame)
{
    if (frame.size() != 11) return;

    uint8_t type = frame[1];

    if (!checkSum(frame)) {
        ROS_WARN("Checksum error");
        return;
    }

#ifdef ONLY_YAW
    if (type == 0x53) {  // 角度
        float yaw = ((int16_t)((frame[7] << 8) | frame[6])) / 32768.0f * 180.0f;
        ROS_INFO("Yaw: %.2f", yaw);

        std_msgs::Float32 msg;
        msg.data = yaw;
        yaw_pub_.publish(msg);
    }
#else
    static sensor_msgs::Imu imu;
    imu.header.stamp = ros::Time::now();
    imu.header.frame_id = "imu_link";

    if (type == 0x53) {
        float roll  = ((int16_t)((frame[3] << 8) | frame[2])) / 32768.0f * 180.0f;
        float pitch = ((int16_t)((frame[5] << 8) | frame[4])) / 32768.0f * 180.0f;
        float yaw   = ((int16_t)((frame[7] << 8) | frame[6])) / 32768.0f * 180.0f;

        tf2::Quaternion q;
        q.setRPY(roll * M_PI/180.0, pitch * M_PI/180.0, yaw * M_PI/180.0);
        q.normalize();

        imu.orientation.x = q.x();
        imu.orientation.y = q.y();
        imu.orientation.z = q.z();
        imu.orientation.w = q.w();
    }

    else if (type == 0x52) {  // 角速度
        imu.angular_velocity.x = ((int16_t)((frame[3] << 8) | frame[2])) / 32768.0f * 2000.0f;
        imu.angular_velocity.y = ((int16_t)((frame[5] << 8) | frame[4])) / 32768.0f * 2000.0f;
        imu.angular_velocity.z = ((int16_t)((frame[7] << 8) | frame[6])) / 32768.0f * 2000.0f;
    }

    else if (type == 0x51) {  // 加速度
        imu.linear_acceleration.x = ((int16_t)((frame[3] << 8) | frame[2])) / 32768.0f * 16.0f;
        imu.linear_acceleration.y = ((int16_t)((frame[5] << 8) | frame[4])) / 32768.0f * 16.0f;
        imu.linear_acceleration.z = ((int16_t)((frame[7] << 8) | frame[6])) / 32768.0f * 16.0f;
    }

    imu.orientation_covariance = {0.01,0,0,0,0.01,0,0,0,0.01};
    imu.angular_velocity_covariance = {0.01,0,0,0,0.01,0,0,0,0.01};
    imu.linear_acceleration_covariance = {0.01,0,0,0,0.01,0,0,0,0.01};

    imu_pub_.publish(imu);
#endif
}

/// ✅ 核心：滑动窗口解析（不会错位）
void SerialReader::readData()
{
    size_t n = serial_.available();
    if (n == 0) return;

    std::vector<uint8_t> data;
    serial_.read(data, n);

    for (auto byte : data) {
        buffer_.push_back(byte);

        // 至少11字节才可能是一帧
        while (buffer_.size() >= 11) {
            if (buffer_[0] != FRAME_HEADER) {
                buffer_.pop_front();  // 丢弃直到找到0x55
                continue;
            }

            std::vector<uint8_t> frame(buffer_.begin(), buffer_.begin() + 11);

            if (checkSum(frame)) {
                parseFrame(frame);
                buffer_.erase(buffer_.begin(), buffer_.begin() + 11);
            } else {
                buffer_.pop_front();  // 校验失败，滑动一位继续找
            }
        }
    }
}

void SerialReader::run()
{
    if (!is_serial_connected_) {
        ROS_ERROR("Serial not connected");
        return;
    }

    ros::Rate loop_rate(50);  // ⭐真正50Hz

    while (ros::ok()) {
        readData();
        ros::spinOnce();
        loop_rate.sleep();
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "imu_node");
    ros::NodeHandle nh;

    SerialReader reader(nh);
    reader.run();

    return 0;
}