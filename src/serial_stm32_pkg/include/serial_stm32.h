#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <ros/ros.h>
#include <serial/serial.h>
#include <processdata_pkg/serial_data.h>
#include <vector>

class SerialCommNode {
public:
    SerialCommNode();
    ~SerialCommNode();
    
    // void run();

private:
void serialDataCallback(const processdata_pkg::serial_data::ConstPtr& msg);
    bool setupSerialPort();
    
    ros::NodeHandle nh_;
    ros::Subscriber serial_data_sub_;
    
    serial::Serial serial_;
    std::string port_;
    int baud_rate_;
};

// uint8_t calculateCRC4(uint8_t byte1, uint8_t byte2, uint8_t byte3_high);
// void packData(uint16_t data, uint8_t& byte1, uint8_t& byte2, uint8_t& byte3);

#endif // SERIAL_COMM_H