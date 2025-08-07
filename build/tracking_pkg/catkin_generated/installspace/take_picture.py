# 拍张照片并保存

#!/usr/bin/env python3
import cv2
import numpy as np
import os
from datetime import datetime

def capture_and_save_photo():
    print("正在初始化摄像头...")
    cap = cv2.VideoCapture(0)
    
    # 设置摄像头参数
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    
    # 验证摄像头
    if not cap.isOpened():
        print("错误：无法打开摄像头")
        return
    
    print("摄像头已就绪，正在拍摄照片...")
    
    # 捕获一帧
    ret, frame = cap.read()
    
    if ret:
        # 创建保存目录（如果不存在）
        save_dir = "captured_photos"
        os.makedirs(save_dir, exist_ok=True)
        
        # 生成带时间戳的文件名
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = os.path.join(save_dir, f"photo_{timestamp}.jpg")
        
        # 保存照片
        cv2.imwrite(filename, frame)
        print(f"照片已保存为: {filename}")
        
        # 显示拍摄的照片（3秒后自动关闭）
        cv2.imshow('Captured Photo', frame)
        cv2.waitKey(3000)
    else:
        print("错误：无法捕获照片")
    
    # 释放资源
    cap.release()
    cv2.destroyAllWindows()
    print("程序退出")

if __name__ == "__main__":
    capture_and_save_photo()