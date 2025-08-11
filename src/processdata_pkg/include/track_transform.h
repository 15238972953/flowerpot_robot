#include <opencv2/opencv.hpp>
#include <iostream>

class PerspectiveTransformer {
public:

    PerspectiveTransformer();

    // 转换单个点
    cv::Point2f transformPoint(const cv::Point2f& point) const;

    // 转换整条直线
    std::pair<cv::Point2f, cv::Point2f> transformLine(const cv::Point2f& p1, const cv::Point2f& p2) const;

private:
    cv::Mat transform_matrix_;

    std::vector<cv::Point2f> slanted_points = {
        {234, 0}, {10, 480}, {550, 420}, {90, 400}  // 斜视视角
    };   

    std::vector<cv::Point2f> front_points = {
        {0, 0}, {320, 480}, {540, 380}, {100, 380}  // 正视视角
    };    

};
