# 利用方形地板进行相机标定，将相机的像素坐标转为实际坐标
import cv2
import numpy as np

# 相机像素点坐标
src_points = np.array([
    [60, 67], [165,65], [166,129], [8,133],  
    [86, 34], [164, 33], [165, 65], [60,67],
    [164,33],[242,30],[271,61],[165,65]   
], dtype=np.float32)

# 实际坐标（相对与相机坐标系）
dst_points = np.array([
    [-61,122], [0,122], [0,61], [-61,61], 
    [-61,183], [0,183], [0,122], [-61,122],
    [0,183],[61,183],[61,122],[0,122] 
], dtype=np.float32)

# 计算 Homography 矩阵（使用 RANSAC 提高鲁棒性）
H, mask = cv2.findHomography(src_points, dst_points, cv2.RANSAC, 5.0)

# 剔除异常点（可选）
src_filtered = src_points[mask.ravel() == 1]
dst_filtered = dst_points[mask.ravel() == 1]

# 重新计算 Homography（仅使用内点）
H_refined, _ = cv2.findHomography(src_filtered, dst_filtered)

# 转换函数，图片中边缘倾倒问题
def pixel_to_world(u, v, H = H_refined):
    point = np.array([[u, v]], dtype=np.float32).reshape(-1, 1, 2)
    transformed_point = cv2.perspectiveTransform(point, H)
    return transformed_point[0, 0, 0], transformed_point[0, 0, 1]

# 示例：计算 (50, 50) 的实际坐标
# u, v = 170.5,179
# x, y = pixel_to_world(u, v, H_refined)
# print(f"实际坐标: ({x:.2f}, {y:.2f})")