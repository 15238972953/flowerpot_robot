#!/usr/bin/env python3
import cv2
import numpy as np
import math

def line_to_line_distance(line1, line2):
    """计算两条线段之间的平均点到直线距离"""
    x1, y1, x2, y2 = line1
    x3, y3, x4, y4 = line2
    
    # 计算line1的直线方程: Ax + By + C = 0
    A1 = y2 - y1
    B1 = x1 - x2
    C1 = x2*y1 - x1*y2
    
    # 计算line2的端点(x3,y3)和(x4,y4)到line1的距离
    def point_to_line_dist(x, y, A, B, C):
        return abs(A*x + B*y + C) / np.sqrt(A**2 + B**2)
    
    dist1 = point_to_line_dist(x3, y3, A1, B1, C1)
    dist2 = point_to_line_dist(x4, y4, A1, B1, C1)
    
    # 对称计算line2到line1的距离
    A2 = y4 - y3
    B2 = x3 - x4
    C2 = x4*y3 - x3*y4
    
    dist3 = point_to_line_dist(x1, y1, A2, B2, C2)
    dist4 = point_to_line_dist(x2, y2, A2, B2, C2)
    
    return (dist1 + dist2 + dist3 + dist4) / 4

def draw_two_lines_with_angle(angle_diff, img_size=(500, 500), line_length=200, line_color1=(0, 0, 255), line_color2=(0, 255, 0), line_thickness=2):
    """
    在图像上绘制两条具有指定角度差的直线
    
    参数:
        angle_diff: 两条线的角度差值(度)
        img_size: 图像尺寸，元组(width, height)
        line_length: 线的长度
        line_color1: 第一条线的颜色，BGR格式
        line_color2: 第二条线的颜色，BGR格式
        line_thickness: 线的粗细
    返回:
        img: 绘制了两条线的图像
    """
    # 创建空白图像
    img = np.ones((img_size[1], img_size[0], 3), dtype=np.uint8) * 255  # 白色背景
    
    # 计算图像中心点
    center_x, center_y = img_size[0] // 2, img_size[1] // 2
    
    # 第一条线的角度设为0度(水平向右)
    angle1 = 0
    # 第二条线的角度为第一条线角度加上角度差
    angle2 = angle1 + angle_diff
    
    # 将角度转换为弧度
    rad1 = math.radians(angle1)
    rad2 = math.radians(angle2)
    
    # 计算第一条线的两个端点
    x1_1 = center_x - int(line_length * math.cos(rad1))
    y1_1 = center_y - int(line_length * math.sin(rad1))
    x1_2 = center_x + int(line_length * math.cos(rad1))
    y1_2 = center_y + int(line_length * math.sin(rad1))
    
    # 计算第二条线的两个端点
    x2_1 = center_x - int(line_length * math.cos(rad2))
    y2_1 = center_y - int(line_length * math.sin(rad2))
    x2_2 = center_x + int(line_length * math.cos(rad2))
    y2_2 = center_y + int(line_length * math.sin(rad2))
    line1 = (x1_1, y1_1, x1_2, y1_2)
    line2 = (x2_1, y2_1, x2_2, y2_2)
    dis = line_to_line_distance(line1, line2)
    print(f"Distance between lines: {dis}")
    # 绘制两条线
    cv2.line(img, (x1_1, y1_1), (x1_2, y1_2), line_color1, line_thickness)
    cv2.line(img, (x2_1, y2_1), (x2_2, y2_2), line_color2, line_thickness)
    
    # 在图像上添加角度差文本说明
    text = f"Angle Difference: {angle_diff} degrees"
    cv2.putText(img, text, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 0), 2)
    
    return img

if __name__ == "__main__":
    # 可以修改这里的角度差值来观察效果
    angle_difference = 1  # 两条线的角度差，单位：度
    
    # 绘制图像
    image = draw_two_lines_with_angle(
        angle_diff=angle_difference,
        img_size=(640, 480),
        line_length=250,
        line_thickness=1
    )
    
    # 显示图像
    cv2.imshow(f"Two Lines with {angle_difference} Degree Difference", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()