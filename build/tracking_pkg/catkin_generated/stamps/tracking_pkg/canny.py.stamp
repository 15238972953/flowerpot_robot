#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import cv2

def canny_edge_detection(image_path, output_path="edges.jpg"):
    # 1. 读取图片（灰度模式）
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    if image is None:
        print("Error: 图片读取失败，请检查路径")
        return

    # 2. 高斯模糊降噪（可选，但推荐用于噪声较多的图片）
    blurred = cv2.GaussianBlur(image, (5, 5), 0)

    # 3. Canny边缘检测
    # 参数说明：
    #   - threshold1: 低阈值（弱边缘筛选）
    #   - threshold2: 高阈值（强边缘筛选）
    #   - apertureSize: Sobel算子大小（默认为3）
    edges = cv2.Canny(blurred, threshold1=50, threshold2=150)

    # 4. 显示结果
    cv2.imshow("Original Image", image)
    cv2.imshow("Canny Edges", edges)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # 5. 保存结果（可选）
    cv2.imwrite(output_path, edges)
    print(f"边缘检测结果已保存至: {output_path}")

# 使用示例
if __name__ == "__main__":
    input_image = "src/tracking_pkg/scripts/captured_photos/photo_20250807_074842.jpg"  # 替换为你的图片路径
    canny_edge_detection(input_image)