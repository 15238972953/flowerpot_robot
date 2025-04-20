#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import LaserScan
import numpy as np
# import matplotlib.pyplot as plt
from sklearn.cluster import DBSCAN
from radar_msgs.msg import radar,array

limit = 3.0

# 圆拟合函数
def fit_circle(x, y):
    A = np.vstack([x, y, np.ones(len(x))]).T
    b = x ** 2 + y ** 2
    c = np.linalg.lstsq(A, b, rcond=None)[0]
    center_x = c[0] / 2
    center_y = c[1] / 2
    radius = np.sqrt(c[2] + center_x ** 2 + center_y ** 2)
    return center_x, center_y, radius



def LidarCallback(msg):

    laser_data = msg.ranges
    # rospy.loginfo(laser_data)
    # 根据激光雷达数据的长度，将角度均匀分布在 [0, 2π] 范围内
    angles = np.linspace(0, 2 * np.pi, len(laser_data))

    laser_data = np.clip(laser_data,a_min=None,a_max=1.0)

    # 根据激光雷达数据和均匀分布的角度，计算 X 和 Y 坐标    
    X = np.array(laser_data) * np.cos(angles)
    Y = np.array(laser_data) * np.sin(angles)

    # 筛选 laser_data 中小于 limit 的有效数据
    # mask_valid = (np.array(laser_data) < limit) & np.isfinite(laser_data)
    mask_valid = np.isfinite(laser_data)
    X_valid = X[mask_valid]
    Y_valid = Y[mask_valid]

    # 组合为二维点坐标数组
    points = np.vstack((X_valid, Y_valid)).T

    # 使用DBSCAN聚类算法对点云进行分簇
    db = DBSCAN(eps=0.1, min_samples=20).fit(points)
    labels = db.labels_

    # 找出簇的数量 (排除噪声点)
    n_clusters = len(set(labels)) - (1 if -1 in labels else 0)

    msg = array()
    # 对每个簇分别拟合圆弧并绘制
    for cluster_idx in range(n_clusters):
        # 提取当前簇的点
        mask = (labels == cluster_idx)
        X_cluster = X_valid[mask]
        Y_cluster = Y_valid[mask]

        # 对簇进行圆拟合
        center_x, center_y, radius = fit_circle(X_cluster, Y_cluster)

        # 输出极坐标信息
        r = np.sqrt(center_x ** 2 + center_y ** 2)
        phi = np.arctan2(center_y, center_x)
        radar_data = radar()
        radar_data.n = cluster_idx
        radar_data.r = r + 0.04
        radar_data.phi = phi
        if radar_data.r < 0.25:
            continue
        msg.array.append(radar_data)

    lidar_pub.publish(msg)
    rospy.loginfo("Publish Radar Data: %s",msg)

if __name__  == "__main__":
    rospy.init_node("PointCloudFitting_node")
    lidar_sub = rospy.Subscriber("/scan",LaserScan,LidarCallback,queue_size=30)
    lidar_pub = rospy.Publisher("Array_Radar",array,queue_size=30)
    rospy.spin()


# Cluster 0 - Center: (r=0.6295, phi=0.3222)
# Cluster 1 - Center: (r=0.4742, phi=-0.2722)

# Cluster 0 - Center: (r=0.6354, phi=0.3256)
# Cluster 1 - Center: (r=0.4770, phi=-0.2687)

# Cluster 0 - Center: (r=0.6352, phi=0.3243)
# Cluster 1 - Center: (r=0.4665, phi=-0.2707)
