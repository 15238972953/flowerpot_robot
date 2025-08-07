import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

yellow_low = [20, 100, 100]
yellow_up = [30, 255, 255]
img = cv.imread('src/tracking_pkg/road.png')
hsv = cv.cvtColor(img, cv.COLOR_BGR2HSV)
mask = cv.inRange(hsv, np.array(yellow_low), np.array(yellow_up))
# 计算沿x轴方向每列的白色像素数量
height, width = mask.shape
x_positions = np.arange(width)
white_pixel_counts = np.sum(mask == 255, axis=0)
# 显示结果
plt.figure(figsize=(12, 5))
plt.subplot(121)
plt.imshow(mask, cmap='gray')
plt.title('Binary Image')
plt.axis('off')
plt.subplot(122)
plt.plot(x_positions, white_pixel_counts)
plt.title('Line Strength')
plt.xlabel('x')
plt.ylabel('white pixel counts')
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.show()