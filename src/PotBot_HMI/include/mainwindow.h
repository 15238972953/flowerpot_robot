#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include "ros_interface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(RosInterface* rosInterface, QWidget *parent = nullptr);
    ~MainWindow();

    // 公有更新函数
    void updateYawAngle(double angle);
    void updateBattery(int value);
    void updateLatitude(double lat);
    void updateLongitude(double lon);
    void updateTransportedPotCount(int count);
    void updateSystemReadyStatus(bool ready);
    bool isFullScreenMode() const { return fullScreenMode; }

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    // 按钮槽函数
    void on_StartLabel_clicked();
    void on_SettingLabel_clicked();
    void on_CloseSettingsBtn_clicked();
    void on_DevModeBtn_clicked();
    
    // 数字键盘按钮
    void on_num1_clicked();
    void on_num2_clicked();
    void on_num3_clicked();
    void on_num4_clicked();
    void on_num5_clicked();
    void on_num6_clicked();
    void on_num7_clicked();
    void on_num8_clicked();
    void on_num9_clicked();
    void on_num0_clicked();
    void on_clearBtn_clicked();
    void on_backspaceBtn_clicked();
    void on_confirmPasswordBtn_clicked();
    void on_cancelPasswordBtn_clicked();
    
    // 堆叠窗口切换信号
    void on_stackedMainArea_currentChanged(int index);
    
    // 标签按钮组
    void on_TabSystemInfo_clicked();
    void on_TabParams_clicked();
    void on_TabDeveloper_clicked();
    void on_TabLog_clicked();
    void on_TabFirmware_clicked();

    void updateRosData();  // 定时更新ROS数据的槽函数

private:
    Ui::MainWindow *ui;
    bool robotRunning;
    bool fullScreenMode;
    QString passwordInput;
    QString correctPassword;

    RosInterface* rosInterface;  // ROS接口指针，允许主窗口调用ROS功能
    QTimer *ros_timer;          // 定时器用于定期调用rosInterface->spinOnce()
    
    void setupDeveloperFeatures();
    void updateTabSelection(QPushButton* selectedTab);
    void showPasswordDialog();
    void hidePasswordDialog();
    void exitFullScreen();
    void adjustFontSizes();
};

#endif // MAINWINDOW_H