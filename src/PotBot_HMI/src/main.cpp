#include "mainwindow.h"
#include <ros/ros.h>
#include <QApplication>
#include <QSurfaceFormat>
#include "ros_interface.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "potbot_hmi_node");

    QApplication app(argc, argv);
    
    // 设置应用程序信息
    QApplication::setApplicationName("PotBot HMI");
    QApplication::setApplicationVersion("2.1.0");
    QApplication::setOrganizationName("Peng Defeng");

    RosInterface rosInterface;  // 创建ROS接口对象，负责与ROS通信
    
    // 创建主窗口
    MainWindow w(&rosInterface);  // 将ROS接口传递给主窗口，允许主窗口调用ROS功能
    
    // 显示主窗口（会自动全屏）
    w.show();
    
    return app.exec();
}