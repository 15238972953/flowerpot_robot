#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QTimer>

// 构造函数
MainWindow::MainWindow(RosInterface *ros, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      robotRunning(false),
      ros_interface(ros)
{
    ui->setupUi(this);

    ui->ReadyStatusValueLabel->setText("Idle");
    ui->BatteryValueLabel->setText("0%");
    ui->YawAngleValueLabel->setText("0");

    ui->LatitudeValueLabel->setText("0.0");
    ui->LongitudeValueLabel->setText("0.0");

    ui->PotCountValueLabel->setText("0");

    // ROS刷新定时器
    ros_timer = new QTimer(this);

    connect(ros_timer, &QTimer::timeout,
            this, &MainWindow::updateRosData);

    ros_timer->start(100); // 10Hz
}

// 析构函数
MainWindow::~MainWindow()
{
    delete ui;
}


// ROS数据更新
void MainWindow::updateRosData()
{
    if(!ros_interface) return;

    // 处理ROS回调
    ros_interface->spinOnce();

    // 更新UI
    updateLatitude(ros_interface->latitude);
    updateLongitude(ros_interface->longitude);
    updateYawAngle(ros_interface->yaw);
}



// 开始运行按钮的槽函数
void MainWindow::on_StartLabel_clicked()
{
    robotRunning = !robotRunning;

    if(robotRunning)
    {
        ui->StartLabel->setText("STOP");
        ui->ReadyStatusValueLabel->setText("Running");

        qDebug() << "Robot Started";

        // 发布ROS启动命令
        if(ros_interface)
        {
            // 读取UI参数
            double spacing = ui->PotSpacingValueLabel->value();
            QString layout = ui->PotLayoutValueLabel->currentText();

            // 发送参数
            ros_interface->publishPotSpacing(spacing);
            ros_interface->publishPotLayout(layout.toStdString());
            ros_interface->publishStart(true);
        }
    }
    else
    {
        ui->StartLabel->setText("START");
        ui->ReadyStatusValueLabel->setText("Stopped");

        qDebug() << "Robot Stopped";

        // 发布ROS停止命令
        if(ros_interface)
            ros_interface->publishStart(false);
    }
}


// 设置按钮的槽函数
void MainWindow::on_SettingLabel_clicked()
{
    QMessageBox::information(
        this,
        "Software Information",
        "PotBot HMI\n"
        "Version: 1.0\n"
        "Author: Peng Defeng\n"
        "Robot: Pot Transport Robot\n"
        "Platform: Jetson Orin Nano"
    );
}


// 更新Yaw角
void MainWindow::updateYawAngle(double angle)
{
    ui->YawAngleValueLabel->setText(QString::number(angle,'f',2));
}


// 更新电量
void MainWindow::updateBattery(int value)
{
    ui->BatteryValueLabel->setText(QString::number(value) + "%");
}


// 更新纬度
void MainWindow::updateLatitude(double lat)
{
    ui->LatitudeValueLabel->setText(QString::number(lat,'f',6));
}


// 更新经度
void MainWindow::updateLongitude(double lon)
{
    ui->LongitudeValueLabel->setText(QString::number(lon,'f',6));
}