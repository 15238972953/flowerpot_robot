cmake_minimum_required(VERSION 3.0.2)
project(PotBot_HMI)

## ROS
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  decision_making_pkg  
)

## Qt
find_package(Qt5 REQUIRED COMPONENTS Widgets)

## Qt 自动处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

## 指定 UI 搜索路径（关键）
set(CMAKE_AUTOUIC_SEARCH_PATHS
  ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

## catkin package
catkin_package(
  CATKIN_DEPENDS roscpp std_msgs decision_making_pkg
)

## include 目录
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${catkin_INCLUDE_DIRS}
)

## 源文件
set(SOURCES
  src/main.cpp
  src/mainwindow.cpp
  src/ros_interface.cpp
)

set(HEADERS
  include/mainwindow.h
  include/ros_interface.h
)

set(UIS
  ui/mainwindow.ui
)

## 可执行文件
add_executable(potbot_hmi_node
  ${SOURCES}
  ${HEADERS}
  ${UIS}
)

## 链接库
target_link_libraries(potbot_hmi_node
  Qt5::Widgets
  ${catkin_LIBRARIES}
)