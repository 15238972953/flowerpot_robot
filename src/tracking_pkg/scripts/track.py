#!/usr/bin/env python3
import cv2
import numpy as np

def capture_camera():
    print("正在初始化摄像头...")
    cap = cv2.VideoCapture(0)
    
    # 设置摄像头参数（可选）
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    
    # 验证摄像头
    if not cap.isOpened():
        print("错误：无法打开摄像头")
        return
    
    print("摄像头已打开，按 'q' 键退出")
    
    # 测试窗口创建
    test_window = cv2.namedWindow('摄像头', cv2.WINDOW_NORMAL)
    cv2.imshow('摄像头', np.zeros((480,640,3), dtype=np.uint8))
    cv2.waitKey(100)
    
    while True:
        ret, frame = cap.read()
        
        if not ret:
            print("警告：帧读取失败")
            # 尝试重新初始化
            cap.release()
            cap = cv2.VideoCapture(0)
            continue
        
        # 显示帧信息（调试用）
        h, w = frame.shape[:2]
        cv2.putText(frame, f"{w}x{h}", (10,30), 
                   cv2.FONT_HERSHEY_SIMPLEX, 1, (0,255,0), 2)
        
        cv2.imshow('摄像头', frame)
        
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    
    cap.release()
    cv2.destroyAllWindows()
    print("摄像头已释放")

if __name__ == "__main__":
    capture_camera()
    print("程序退出")