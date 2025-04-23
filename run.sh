#!/bin/bash

# 脚本功能：启动搬花机器人ROS系统
# 使用方法：./run.sh

# 1. 启动roscore（后台运行）
gnome-terminal --title="ROS Core" -- bash -c "roscore; exec bash" &
echo "[1/4] Roscore 已启动"
sleep 2  # 等待roscore初始化

# 2. 新建终端并修改USB权限，启动雷达驱动节点
gnome-terminal --title="Radar Start" -- bash -c "
echo '[2/4] 启动雷达驱动节点...';
sudo chmod 777 /dev/ttyCH343USB0;
echo '权限已设置：/dev/ttyCH343USB0';
roslaunch lslidar_driver lslidar_serial.launch;
exec bash" &
sleep 2

# 3. 启动所有节点
gnome-terminal --title="All Nodes" -- bash -c "
echo '[3/4] 启动all_node.launch...';
rosrun radar_pkg all_node.launch;
exec bash" &

echo "所有节点已启动完成！"
