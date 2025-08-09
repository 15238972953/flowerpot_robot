#!/usr/bin/env python3
import rospy
import cv2
import numpy as np
from math import sqrt
from itertools import combinations
from tracking_pkg.msg import track

class LineKalmanFilter:
    def __init__(self):
        # 状态变量：[x1, y1, x2, y2, k]
        self.kf = cv2.KalmanFilter(5, 5)
        
        # 状态转移矩阵（假设线性运动）
        self.kf.transitionMatrix = np.array([
            [1, 0, 0, 0, 0],
            [0, 1, 0, 0, 0],
            [0, 0, 1, 0, 0],
            [0, 0, 0, 1, 0],
            [0, 0, 0, 0, 1]
        ], np.float32)
        
        # 观测矩阵（直接观测所有状态）
        self.kf.measurementMatrix = np.array([
            [1, 0, 0, 0, 0],
            [0, 1, 0, 0, 0],
            [0, 0, 1, 0, 0],
            [0, 0, 0, 1, 0],
            [0, 0, 0, 0, 1]
        ], np.float32)
        
        # 过程噪声协方差（调整滤波响应速度）
        self.kf.processNoiseCov = np.eye(5, dtype=np.float32) * 0.01
        
        # 观测噪声协方差（调整对观测的信任度）
        self.kf.measurementNoiseCov = np.eye(5, dtype=np.float32) * 0.1
    
    def is_valid_measurement(self, measurement, threshold=100.0):
        # 计算预测值与观测值的马氏距离（Mahalanobis distance）
        innovation = measurement - self.kf.predict()
        innovation_cov = self.kf.errorCovPre + self.kf.measurementNoiseCov
        mahalanobis_dist = np.sqrt(innovation.T @ np.linalg.inv(innovation_cov) @ innovation).item()
        print("Mahalanobis distance:", mahalanobis_dist)
        # 如果马氏距离过大，则认为是异常值
        return mahalanobis_dist < threshold

    def update(self, x1, y1, x2, y2, k):
        # 预测
        prediction = self.kf.predict()
        
        # 更新观测值
        measurement = np.array([[x1], [y1], [x2], [y2], [k]], np.float32)
        # 如果观测值异常，则跳过更新，仅预测
        if not self.is_valid_measurement(measurement):
            # print("Rejected outlier:", measurement.flatten())
            return self.kf.predict().flatten()  # 返回预测值
        
        # 修正
        self.kf.correct(measurement)
        
        # 返回修正后的状态
        smoothed_state = self.kf.statePost
        return (
            smoothed_state[0, 0],  # x1
            smoothed_state[1, 0],  # y1
            smoothed_state[2, 0],  # x2
            smoothed_state[3, 0],  # y2
            smoothed_state[4, 0]   # k
        )

def line_to_line_distance_ratio(line1, line2):
    """
    计算较短线段两端点到较长直线的垂直距离占自身长度的比例
    返回: (距离比例)
    """
    # 解包线段坐标
    x1, y1, x2, y2 = line1
    x3, y3, x4, y4 = line2
    
    # 计算两条线段的长度
    len1 = np.sqrt((x2-x1)**2 + (y2-y1)**2)
    len2 = np.sqrt((x4-x3)**2 + (y4-y3)**2)
    
    # 确定较长和较短的线段
    if len1 >= len2:
        long_line, short_line = (x1, y1, x2, y2), (x3, y3, x4, y4)
        short_len = len2
    else:
        long_line, short_line = (x3, y3, x4, y4), (x1, y1, x2, y2)
        short_len = len1
    
    # 计算较长直线的方程: Ax + By + C = 0
    xl1, yl1, xl2, yl2 = long_line
    A = yl2 - yl1
    B = xl1 - xl2
    C = xl2*yl1 - xl1*yl2
    
    # 计算较短线段两个端点到较长直线的距离
    def point_to_line_dist(x, y):
        return abs(A*x + B*y + C) / np.sqrt(A**2 + B**2)
    
    # 获取较短线段的两个端点
    xs1, ys1, xs2, ys2 = short_line
    
    # 计算两个端点的距离
    dist1 = point_to_line_dist(xs1, ys1)
    dist2 = point_to_line_dist(xs2, ys2)
    
    # 计算距离比例（距离/线段长度）
    ratio = (dist1 + dist2) / short_len

    return ratio

def merge_lines(lines, angle_thresh=5.0, dist_thresh=20.0, overlap_thresh=0.3):
    """合并共线线段"""
    if lines is None or len(lines) == 0:
        return np.empty((0,4), dtype=np.int32)
    
    # 统一转换为 (N,4) 格式
    lines = lines.reshape(-1,4) if len(lines.shape) == 3 else lines
    
    # 计算直线参数
    line_params = []
    for x1, y1, x2, y2 in lines:
        if x1 != x2:
            k = (y2 - y1) / (x2 - x1)
            b = y1 - k * x1
            line_params.append(('k', k, b, x1, y1, x2, y2))
        else:
            line_params.append(('v', x1, None, x1, y1, x2, y2))

    # 聚类相似直线
    clusters = []
    for param in line_params:
        line_type, *rest = param
        matched = False
        
        for cluster in clusters:
            if line_type == cluster['type']:
                if line_type == 'k':
                    # 获取当前聚类中的参考直线（取第一条）
                    ref_line = cluster['lines'][0][2:]  # 取出x1,y1,x2,y2
                    current_line = rest[2:]  # 当前直线的x1,y1,x2,y2
                    avg_k, avg_b = cluster['avg']
                    k, b, _, _, _, _ = rest
                    angle_diff = np.degrees(np.abs(np.arctan(k) - np.arctan(avg_k)))
                    overlap_ratio = line_to_line_distance_ratio(ref_line, current_line)
                    if angle_diff < angle_thresh and overlap_ratio < overlap_thresh:
                        cluster['lines'].append(rest)
                        cluster['avg'] = np.mean([x[:2] for x in cluster['lines']], axis=0)
                        matched = True
                # else:  # 'v'
                #     avg_x = cluster['avg'][0]
                #     x, _, _, _, _, _ = rest
                #     if np.abs(x - avg_x) < dist_thresh:
                #         cluster['lines'].append(rest)
                #         cluster['avg'] = np.mean([x[:1] for x in cluster['lines']], axis=0)
                #         matched = True
                if matched:
                    break
        
        if not matched:
            clusters.append({
                'type': line_type,
                'lines': [rest],
                'avg': rest[:2] if line_type == 'k' else rest[:1]
            })
    
    # 生成合并后的直线
    merged = []
    for cluster in clusters:
        if cluster['type'] == 'k':
            points = []
            for (_, _, x1, y1, x2, y2) in cluster['lines']:
                points.extend([(x1,y1), (x2,y2)])
            points = np.array(points)
            
            # 拟合直线
            [vx, vy, x0, y0] = cv2.fitLine(points, cv2.DIST_L2, 0, 0.01, 0.01).flatten()
            k = vy / vx
            b = y0 - k * x0
            
            # 计算新端点
            xs = [p[0] for p in points]
            x_min, x_max = min(xs), max(xs)
            y1 = int(k * x_min + b)
            y2 = int(k * x_max + b)
            merged.append([x_min, y1, x_max, y2])
        # else:  # 垂直线
        #     ys = []
        #     x = cluster['avg'][0]
        #     for (_, _, y1, _, y2, _) in cluster['lines']:
        #         ys.extend([y1, y2])
        #     y_min, y_max = min(ys), max(ys)
        #     merged.append([x, y_min, x, y_max])
    
    return merged

def is_valid_black_line(mask, line, check_distance=5, points_per_side=10, diff_threshold=0.3):
    """
    检查是否为真实黑线（通过比较两侧垂直方向的像素值）
    :param mask: 二值化掩膜（黑色区域为0，白色为255）
    :param line: 直线坐标 [x1,y1,x2,y2]
    :param check_distance: 检查的垂直距离（像素）
    :param points_per_side: 每侧采集的点数
    :param diff_threshold: 允许的最大不同值比例（0-1）
    :return: True/False
    """
    x1, y1, x2, y2 = line
    
    # 计算直线的方向向量和法向量
    dx = x2 - x1
    dy = y2 - y1
    length = np.sqrt(dx*dx + dy*dy)
    
    # 归一化方向向量和法向量
    if length > 0:
        dx, dy = dx/length, dy/length
    nx, ny = -dy, dx  # 单位法向量
    
    # 沿直线均匀分布的采样点
    sample_points = []
    for i in np.linspace(0, 1, points_per_side):
        x = x1 + i * (x2 - x1)
        y = y1 + i * (y2 - y1)
        sample_points.append((x, y))
    
    # 存储两侧的采样点值
    left_side = []
    right_side = []
    
    for (x, y) in sample_points:
        # 左侧点（法线负方向）
        left_x = int(x - nx * check_distance)
        left_y = int(y - ny * check_distance)
        
        # 右侧点（法线正方向）
        right_x = int(x + nx * check_distance)
        right_y = int(y + ny * check_distance)
        
        # 边界检查并收集像素值
        if 0 <= left_x < mask.shape[1] and 0 <= left_y < mask.shape[0]:
            left_side.append(mask[left_y, left_x])
        else:
            left_side.append(0)  # 边界外默认为黑色
        
        if 0 <= right_x < mask.shape[1] and 0 <= right_y < mask.shape[0]:
            right_side.append(mask[right_y, right_x])
        else:
            right_side.append(0)  # 边界外默认为黑色
    
    # 比较两侧对应位置的像素值
    diff_count = 0
    total_comparisons = min(len(left_side), len(right_side))
    
    for i in range(total_comparisons):
        if left_side[i] != right_side[i]:
            diff_count += 1
    
    # 如果不同值比例超过阈值，返回False
    if diff_count / total_comparisons > diff_threshold:
        return False
    
    return True

def detect_black_line_from_camera():

    rospy.init_node("tracking_node")
    track_pub = rospy.Publisher("track_msg",track,queue_size=30)

    # 初始化摄像头
    cap = cv2.VideoCapture(0)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    if not cap.isOpened():
        print("Error: 无法打开摄像头")
        return

    # 初始化卡尔曼滤波器
    kf = LineKalmanFilter()
    
    while True:
        # 1. 读取视频帧
        ret, frame = cap.read()
        if not ret:
            print("Error: 无法读取视频帧")
            break
        
        # 2. 预处理
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        lower_black = np.array([0, 48, 0])
        upper_black = np.array([110, 146, 117])
        mask = cv2.inRange(hsv, lower_black, upper_black)


        # 3. 形态学操作
        kernel = np.ones((15,15), np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
        cv2.imshow('Mask Result', mask)
        # 4. 边缘检测
        edges = cv2.Canny(mask, 100, 150)

        # 5. 霍夫变换检测直线
        lines = cv2.HoughLinesP(
            edges,
            rho=1,
            theta=np.pi/180,
            threshold=30,
            minLineLength=70,
            maxLineGap=10
        )

        # 6. 绘制检测到的直线（优化版）
        if lines is not None:
            lines = merge_lines(lines)
            # 画出所有检测到的直线
            for line in lines:
                if len(line) == 4:
                    x1, y1, x2, y2 = line
                    
                    if is_valid_black_line(mask, line, check_distance=5, points_per_side=10, diff_threshold=0.5):
                        
                        length = np.sqrt((x2 - x1)**2 + (y2 - y1)**2)
                
                        if length > 200:
                            k = (y2 - y1) / (x2 - x1)
                            x1, y1, x2, y2, k = kf.update(x1, y1, x2, y2, k)
                            cv2.line(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                            track_msg = track()
                            track_msg.line[0] = x1
                            track_msg.line[1] = y1
                            track_msg.line[2] = x2
                            track_msg.line[3] = y2
                            track_pub.publish(track_msg)
                            print(f"直线坐标: ({x1},{y1})->({x2},{y2}), leng: {length:.2f} ")

            # 找出最长的直线
            # longest_line = max(lines, key=lambda line: (line[2]-line[0])**2 + (line[3]-line[1])**2)
            # x1, y1, x2, y2 = longest_line

            
            # # 延长直线到画面边缘
            # height, width = frame.shape[:2]
            
            # # 计算直线参数 y = kx + b
            # if x1 != x2:
            #     k = (y2 - y1) / (x2 - x1)
            #     smoothed_x1, smoothed_y1, smoothed_x2, smoothed_y2, smoothed_k = kf.update(x1, y1, x2, y2, k)
            #     # smoothed_x1, smoothed_y1, smoothed_x2, smoothed_y2, smoothed_k = x1, y1, x2, y2, k
            #     print(f"Detected line: ({x1}, {y1}) to ({x2}, {y2}) -> Smoothed: ({smoothed_x1:.2f}, {smoothed_y1:.2f}) to ({smoothed_x2:.2f}, {smoothed_y2:.2f})")
            #     b = smoothed_y1 - smoothed_k * smoothed_x1
            #     # 计算与左右边界的交点
            #     x_left = 0
            #     y_left = int(smoothed_k * x_left + b)
                
            #     x_right = width
            #     y_right = int(smoothed_k * x_right + b)
                
            #     # 确保交点在画面内
            #     if 0 <= y_left <= height and 0 <= y_right <= height:
            #         cv2.line(frame, (x_left, y_left), (x_right, y_right), (0, 0, 255), 3)
            #     else:
            #         # 计算与上下边界的交点
            #         y_top = 0
            #         x_top = int((y_top - b) / smoothed_k) if smoothed_k != 0 else x1
                    
            #         y_bottom = height
            #         x_bottom = int((y_bottom - b) / smoothed_k) if smoothed_k != 0 else x1
                    
            #         if 0 <= x_top <= width:
            #             cv2.line(frame, (int(x_top), int(y_top)), (int(smoothed_x1), int(smoothed_y1)), (0, 0, 255), 3)
            #             # print(f"({x_top}, {y_top}) to ({x1}, {y1}), k = {k:.2f}")
            #         if 0 <= x_bottom <= width:
            #             cv2.line(frame, (int(x_bottom), int(y_bottom)), (int(smoothed_x1), int(smoothed_y1)), (0, 0, 255), 3)
            #             # print(f"({x_bottom}, {y_bottom}) to ({x1}, {y1}), k = {k:.2f}")
            # else:  # 垂直线
            #     cv2.line(frame, (x1, 0), (x1, height), (0, 0, 255), 3)

        # 7. 显示结果
        cv2.imshow('Black Line Detection', frame)
        
        # 按ESC退出
        if cv2.waitKey(1) == 27:
            break

    # 释放资源
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    try:
        detect_black_line_from_camera()
    except rospy.ROSInterruptException:
        pass