#!/bin/bash

# 脚本功能：启动搬花机器人ROS系统
# 使用方法：./run.sh

# 1. 启动roscore（后台运行）
gnome-terminal --title="ROS Core" -- bash -c "roscore; exec bash" &
echo "[1/12] Roscore 已启动"
sleep 2  # 等待roscore初始化

# 2. 新建终端并修改USB权限，启动雷达驱动节点
gnome-terminal --title="Radar Start" -- bash -c "
echo '[2/12] 启动雷达驱动节点...';
sudo chmod 777 /dev/ttyCH343USB0;
echo '权限已设置：/dev/ttyCH343USB0';
roslaunch lslidar_driver lslidar_serial.launch;
exec bash" &
sleep 2

# 3. 启动radar节点
gnome-terminal --title="radar Nodes" -- bash -c "
echo '[3/12] 启动camera.launch...';    
roslaunch radar_pkg radar.launch;
exec bash" &

# 4. 启动camera节点
gnome-terminal --title="camera Nodes" -- bash -c "
echo '[4/12] 启动camera.launch...';    
roslaunch camera_pkg camera.launch;
exec bash" &

# 5. 启动yolo11节点
gnome-terminal --title="yolo11 Nodes" -- bash -c "
echo '[5/12] 启动yolo11.launch...';    
roslaunch yolo11_pkg yolo11.launch;
exec bash" &

# 6. 启动IMU节点
gnome-terminal --title="IMU Nodes" -- bash -c "
echo '[6/12] 启动imu.launch...';   
sudo chmod 777 /dev/ttyUSB0 
roslaunch imu_pkg imu.launch;
exec bash" &

# 7. 启动GPS节点
gnome-terminal --title="GPS Nodes" -- bash -c "
echo '[7/12] 启动GPS.launch...';   
sudo chmod 777 /dev/ttyACM3 
roslaunch GPS_pkg GPS.launch;
exec bash" &

# 8. 启动HMI节点
gnome-terminal --title="HMI Nodes" -- bash -c "
echo '[8/12] 启动potbot_hmi.launch...';    
roslaunch PotBot_HMI potbot_hmi.launch;
exec bash" &

# 9. 启动serial_stm32节点
gnome-terminal --title="serial_stm32 Nodes" -- bash -c "
echo '[9/12] 启动serial_stm32.launch...'; 
sudo chmod 777 /dev/ttyTHS0  
roslaunch serial_stm32_pkg serial_stm32.launch;
exec bash" &

# 10. 启动system_monitor节点
gnome-terminal --title="system_monitor Nodes" -- bash -c "
echo '[10/12] 启动system_monitor.launch...';  
roslaunch system_monitor system_monitor.launch;
exec bash" &

# 11. 启动 processdata 节点
gnome-terminal --title="processdata Nodes" -- bash -c "
echo '[11/12] 启动 processdata.launch...';  
roslaunch processdata_pkg processdata.launch;
exec bash" &

# 12. 启动 decision_making 节点
gnome-terminal --title="decision_making Nodes" -- bash -c "
echo '[12/12] 启动 decision_making.launch...';  
roslaunch decision_making_pkg decision_making.launch;
exec bash" &

echo "所有节点已启动完成！"
