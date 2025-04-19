#ifndef HUNGARIAN_ALGORITHM_H
#define HUNGARIAN_ALGORITHM_H

#include <vector>

// 二维点结构
struct Point {
    double x;
    double y;
    Point(double _x = 0, double _y = 0);
};

// 匈牙利算法类
class HungarianAlgorithm {
public:
    HungarianAlgorithm(const std::vector<std::vector<double>>& cost_matrix);
    std::vector<int> solve();

private:
    std::vector<std::vector<double>> cost;
    int N, M;
    std::vector<double> u, v;
    std::vector<int> p, way;
};

// 计算欧氏距离
double euclideanDistance(const Point& p1, const Point& p2);

// 使用匈牙利算法进行数据关联
std::vector<std::pair<int, int>> associatePoints(
        const std::vector<Point>& sensor1_points,
        const std::vector<Point>& sensor2_points,
        double max_distance = 50);

#endif // HUNGARIAN_ALGORITHM_H