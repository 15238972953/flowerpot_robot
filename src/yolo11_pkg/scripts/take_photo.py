#!/usr/bin/env python3
import cv2

# 打开相机，拍照，保存
cap = cv2.VideoCapture(0)
ret, frame = cap.read()
cv2.imwrite("/home/jetson/catkin_ws/picture/photo.png", frame)
cap.release()
print("照片已保存: /home/jetson/catkin_ws/picture/photo.png")