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

# 全局变量
roi = None
drawing = False
ix, iy = -1, -1
fx, fy = -1, -1
h_low, h_high = 0, 179
s_low, s_high = 0, 255
v_low, v_high = 0, 255

def select_roi(event, x, y, flags, param):
    global ix, iy, fx, fy, drawing, roi
    
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        ix, iy = x, y
        
    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing:
            img_copy = img.copy()
            cv2.rectangle(img_copy, (ix, iy), (x, y), (0, 255, 0), 2)
            cv2.imshow('Select ROI (Drag & Release)', img_copy)
            
    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        fx, fy = x, y
        roi = img[min(iy,fy):max(iy,fy), min(ix,fx):max(ix,fx)]
        if roi.size == 0:
            print("错误：ROI区域无效！")
            return
        
        # 自动计算初始HSV范围
        auto_calculate_hsv(roi)
        update_display()

def auto_calculate_hsv(roi):
    global h_low, h_high, s_low, s_high, v_low, v_high
    
    hsv_roi = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
    
    # 计算HSV统计值
    h_mean, h_std = np.mean(hsv_roi[:,:,0]), np.std(hsv_roi[:,:,0])
    s_mean, s_std = np.mean(hsv_roi[:,:,1]), np.std(hsv_roi[:,:,1])
    v_mean, v_std = np.mean(hsv_roi[:,:,2]), np.std(hsv_roi[:,:,2])
    
    # 自动计算阈值范围（±2倍标准差）
    h_low = max(0, int(h_mean - 2*h_std))
    h_high = min(179, int(h_mean + 2*h_std))
    s_low = max(0, int(s_mean - 2*s_std))
    s_high = min(255, int(s_mean + 2*s_std))
    v_low = max(0, int(v_mean - 2*v_std))
    v_high = min(255, int(v_mean + 2*v_std))
    
    # 更新滑动条位置
    cv2.setTrackbarPos('H Low', 'HSV Controls', h_low)
    cv2.setTrackbarPos('H High', 'HSV Controls', h_high)
    cv2.setTrackbarPos('S Low', 'HSV Controls', s_low)
    cv2.setTrackbarPos('S High', 'HSV Controls', s_high)
    cv2.setTrackbarPos('V Low', 'HSV Controls', v_low)
    cv2.setTrackbarPos('V High', 'HSV Controls', v_high)
    
    print("\n自动计算的HSV阈值范围:")
    print(f"Lower: [{h_low}, {s_low}, {v_low}]")
    print(f"Upper: [{h_high}, {s_high}, {v_high}]")

def update_display(*args):
    global roi, h_low, h_high, s_low, s_high, v_low, v_high
    
    if roi is None:
        return
    
    # 获取当前滑动条值
    h_low = cv2.getTrackbarPos('H Low', 'HSV Controls')
    h_high = cv2.getTrackbarPos('H High', 'HSV Controls')
    s_low = cv2.getTrackbarPos('S Low', 'HSV Controls')
    s_high = cv2.getTrackbarPos('S High', 'HSV Controls')
    v_low = cv2.getTrackbarPos('V Low', 'HSV Controls')
    v_high = cv2.getTrackbarPos('V High', 'HSV Controls')
    
    # 应用HSV阈值
    hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
    lower = np.array([h_low, s_low, v_low])
    upper = np.array([h_high, s_high, v_high])
    mask = cv2.inRange(hsv, lower, upper)
    res = cv2.bitwise_and(roi, roi, mask=mask)
    
    # 显示结果
    display = np.hstack((roi, cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR), res))
    cv2.imshow('Mask Result', display)

if __name__ == "__main__":
    # 读取图片（修改为你的图片路径）
    img_path = '/home/jetson/catkin_ws/src/tracking_pkg/road.jpg'  # 或者使用绝对路径
    img = cv2.imread(img_path)
    
    if img is None:
        print(f"错误：无法加载图片 {img_path}")
        print("请检查：")
        print("1. 图片是否存在")
        print("2. 文件路径是否正确")
        print("3. 文件是否有读取权限")
        exit()
    
    # 创建控制窗口
    cv2.namedWindow('HSV Controls')
    cv2.createTrackbar('H Low', 'HSV Controls', 0, 179, update_display)
    cv2.createTrackbar('H High', 'HSV Controls', 179, 179, update_display)
    cv2.createTrackbar('S Low', 'HSV Controls', 0, 255, update_display)
    cv2.createTrackbar('S High', 'HSV Controls', 255, 255, update_display)
    cv2.createTrackbar('V Low', 'HSV Controls', 0, 255, update_display)
    cv2.createTrackbar('V High', 'HSV Controls', 255, 255, update_display)
    
    # 创建ROI选择窗口
    cv2.namedWindow('Select ROI (Drag & Release)')
    cv2.setMouseCallback('Select ROI (Drag & Release)', select_roi)
    
    print("操作指南：")
    print("1. 在'Select ROI'窗口拖动鼠标框选感兴趣区域")
    print("2. 使用'HSV Controls'窗口的滑动条调整阈值")
    print("3. 按q键退出程序")
    
    cv2.imshow('Select ROI (Drag & Release)', img)
    
    while True:
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            break
    
    cv2.destroyAllWindows()
    
    # 输出最终阈值
    print("\n最终HSV阈值范围:")
    print(f"Lower: [{h_low}, {s_low}, {v_low}]")
    print(f"Upper: [{h_high}, {s_high}, {v_high}]")