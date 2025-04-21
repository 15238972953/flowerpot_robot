#ifndef HUNGARIAN_ALGORITHM_H
#define HUNGARIAN_ALGORITHM_H

#include <vector>
#include <eigen3/Eigen/Dense>

// 二维点结构
struct Point {
    float x;
    float y;
    Point(float _x = 0, float _y = 0);

    Eigen::Vector2d toVector2d() const {
        return Eigen::Vector2d(x, y);
    }
};

// 匈牙利算法类
class HungarianAlgorithm {
public:
    HungarianAlgorithm(const std::vector<std::vector<float>>& cost_matrix);
    std::vector<int> solve();

private:
    std::vector<std::vector<float>> cost;
    int N, M;
    std::vector<float> u, v;
    std::vector<int> p, way;
};

// 计算欧氏距离
float euclideanDistance(const Point& p1, const Point& p2);

// 使用匈牙利算法进行数据关联
std::vector<std::pair<Point, Point>> associatePoints(
        const std::vector<Point>& sensor1_points,
        const std::vector<Point>& sensor2_points,
        float max_distance);

#endif // HUNGARIAN_ALGORITHM_H