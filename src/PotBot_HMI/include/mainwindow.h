#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "ros_interface.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(RosInterface *ros, QWidget *parent = nullptr);
    ~MainWindow();

    // UI数据显示接口
    void updateYawAngle(double angle);
    void updateBattery(int value);
    void updateLatitude(double lat);
    void updateLongitude(double lon);

private slots:

    // 开始运行按钮的槽函数
    void on_StartLabel_clicked();

    // 设置按钮的槽函数
    void on_SettingLabel_clicked();

    // ROS数据刷新
    void updateRosData();

private:

    Ui::MainWindow *ui;

    bool robotRunning;

    // ROS接口
    RosInterface *ros_interface;

    // 定时器，用于定期刷新ROS数据
    QTimer *ros_timer;
};

#endif