# 使用说明：
# 一、准备阶段：
# 1、将脚本中的your_image.jpg替换为你的图片路径
# 2、确保已安装OpenCV：pip install opencv-python
# 二、操作步骤：
# 1、运行脚本后会显示原始图片
# 2、鼠标拖动选择感兴趣区域(ROI)
# 3、程序会自动计算初始HSV范围
# 4、使用滑动条微调阈值范围
# 5、实时查看掩膜效果
# 6、按q键退出并获取最终阈值

#!/usr/bin/env python3
import cv2
import numpy as np

def nothing(x):
    pass

# 初始化窗口和滑动条
cv2.namedWindow('Threshold Adjuster')
cv2.createTrackbar('H_min', 'Threshold Adjuster', 0, 179, nothing)
cv2.createTrackbar('H_max', 'Threshold Adjuster', 179, 179, nothing)
cv2.createTrackbar('S_min', 'Threshold Adjuster', 0, 255, nothing)
cv2.createTrackbar('S_max', 'Threshold Adjuster', 255, 255, nothing)
cv2.createTrackbar('V_min', 'Threshold Adjuster', 0, 255, nothing)
cv2.createTrackbar('V_max', 'Threshold Adjuster', 255, 255, nothing)

# 读取图像
image = cv2.imread('/home/jetson/catkin_ws/src/tracking_pkg/scripts/captured_photos/photo_20250807_074842.jpg')
hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

while True:
    # 获取滑动条当前位置
    h_min = cv2.getTrackbarPos('H_min', 'Threshold Adjuster')
    h_max = cv2.getTrackbarPos('H_max', 'Threshold Adjuster')
    s_min = cv2.getTrackbarPos('S_min', 'Threshold Adjuster')
    s_max = cv2.getTrackbarPos('S_max', 'Threshold Adjuster')
    v_min = cv2.getTrackbarPos('V_min', 'Threshold Adjuster')
    v_max = cv2.getTrackbarPos('V_max', 'Threshold Adjuster')
    
    # 设定HSV阈值范围
    lower = np.array([h_min, s_min, v_min])
    upper = np.array([h_max, s_max, v_max])
    
    # 生成掩膜
    mask = cv2.inRange(hsv, lower, upper)
    result = cv2.bitwise_and(image, image, mask=mask)
    
    # 显示结果
    cv2.imshow('Original', image)
    cv2.imshow('Mask', mask)
    cv2.imshow('Result', result)
    
    # 按ESC退出
    if cv2.waitKey(1) == 27:
        break

# 打印最终选择的阈值
print(f"Final HSV Threshold: Lower={lower}, Upper={upper}")
cv2.destroyAllWindows()