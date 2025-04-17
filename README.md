# 1、项目描述

```
catkin_ws ————工作空间
	|——— build/                                  # 编译空间，用于存放CMake和catkin的缓存信息、配置信息和其他中间文件
	|——— devel/                                  # 开发空间，用于存放编译后生成的目标文件，包括头文件、动态&静态链接库、可执行文件等
	|——— src/                                    # 源码
	| 	  |--- lsx10/                            # 激光雷达驱动文件
	|     |--- processdata_pkg/                  # 相机和雷达的数据进行处理融合操作
	|     |--- radar_msgs/                       # 雷达消息数据
	|     |        |--- msg/                     # 雷达数据包
	|     |        |--- CMakeLists.txt           # 配置编译规则
	|     |        |--- package.xml              # 包信息
	|     |--- radar_pkg/                        # 雷达数据处理
	|     |        |--- src/                     # python处理雷达数据代码
	|     |        |--- CMakeLists.txt           # 配置编译规则
	|     |        |--- package.xml              # 包信息
	|     |--- yolo11_pkg/                       # 相机视觉识别调用部分代码
 	|     |        |--- msg/                     # 相机数据包
 	|     |        |--- scripts/                 # 相机调用代码及所需文件
	|     |        |--- CMakeLists.txt           # 配置编译规则
	|     |        |--- package.xml              # 包信息
	|     |--- CMakeLists.txt                    # 配置编译规则
    |     |--- radar_note.txt                    # 部分命令记录
```



# 2 、ROS基础

**ros文件系统如下所示：**

![image-20250416203205223](.\picture\image-20250416203205223.png)

**准备步骤：**

```bash
//创建工作空间并初始化
mkdir -p catkin_ws/src
cd catkin_ws
catkin_make

//进入 src 创建 ros 包并添加依赖
cd src
catkin_create_pkg name_pkg roscpp rospy std_msgs

cd ./catkin_ws/src

//从src打开vscode
code .
//在包中的src下创建节点文件.cpp，进行编程
```

# 3、运行出rviz点云步骤

1，启动ros核心:`roscore`

插上雷达后，参考轮趣科技（自己的激光雷达的商家）提供的说明文档。

2，终端运行：`ll /dev/|grep ttyCH343USB`

3，终端运行：`sudo chmod 777 /dev/ttyCH343USB0`将接口的权限修改为最大；

4，启动雷达：`roslaunch lslidar_driver lslidar_serial_launch`

5，测试是否成功：`rostopic echo /scan`

5，运行rviz：`rviz`，选择参数，即可显示出点云；

# 4、雷达输出点云拟合的圆形花盆坐标

需安装：对应的库（yaml，rospkg，scikit-learn等库，不要装plt的库（没用到）），以后应该就不需要安装了；

在`roscore`和 `roslaunch lslidar_driver lslidar_serial_launch`的前提下，

在catkin_ws目录下运行 `rosrun radar_pkg PointCloudFitting_node.py`即可在终端输出花盆的极坐标信息；

相机识别帧率大概36帧，激光雷达节点输出帧率为12帧；

# 5、相机和雷达数据的处理

radar和yolo11发布节点，process_data中订阅节点并处理

# 更新中。。。
