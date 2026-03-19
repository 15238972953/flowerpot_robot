#include <QApplication>
#include <ros/ros.h>
#include "mainwindow.h"
#include "ros_interface.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "potbot_hmi_node");

    QApplication app(argc, argv);

    RosInterface ros_interface;

    MainWindow w(&ros_interface);
    w.show();

    return app.exec();
}