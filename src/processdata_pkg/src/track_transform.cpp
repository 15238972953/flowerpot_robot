#include "track_transform.h"

// 构造函数，接受对应点初始化变换矩阵
PerspectiveTransformer::PerspectiveTransformer() {
    if (slanted_points.size() != 4 || front_points.size() != 4) {
        throw std::runtime_error("需要4组对应点");
    }
    transform_matrix_ = cv::getPerspectiveTransform(slanted_points, front_points);
}

// 转换单个点
cv::Point2f PerspectiveTransformer::transformPoint(const cv::Point2f& point) const {
    std::vector<cv::Point2f> src = {point};
    std::vector<cv::Point2f> dst;
    cv::perspectiveTransform(src, dst, transform_matrix_);
    return dst[0];
}

// 转换整条直线
std::pair<cv::Point2f, cv::Point2f> PerspectiveTransformer::transformLine(const cv::Point2f& p1, 
                                                    const cv::Point2f& p2) const {
    return {transformPoint(p1), transformPoint(p2)};
}
