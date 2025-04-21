#include "HungarianAlgorithm.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>

// Point结构实现
Point::Point(float _x, float _y) : x(_x), y(_y) {}

// 匈牙利算法实现
HungarianAlgorithm::HungarianAlgorithm(const std::vector<std::vector<float>>& cost_matrix)
        : cost(cost_matrix), N(cost_matrix.size()), M(cost_matrix.empty() ? 0 : cost_matrix[0].size()) {
    u.assign(N + 1, 0);
    v.assign(M + 1, 0);
    p.assign(M + 1, 0);
    way.assign(M + 1, 0);
}

std::vector<int> HungarianAlgorithm::solve() {
    std::vector<int> assignment(N, -1);  // 初始化为-1表示未匹配

    if (N == 0 || M == 0) {
        return assignment;
    }

    for (int i = 1; i <= N; ++i) {
        p[0] = i;
        int j0 = 0;
        std::vector<float> minv(M + 1, std::numeric_limits<float>::max());
        std::vector<bool> used(M + 1, false);

        do {
            used[j0] = true;
            int i0 = p[j0], j1;
            float delta = std::numeric_limits<float>::max();

            for (int j = 1; j <= M; ++j) {
                if (!used[j]) {
                    float cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }

            for (int j = 0; j <= M; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }

            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }

    for (int j = 1; j <= M; ++j) {
        if (p[j] != 0) {
            assignment[p[j] - 1] = j - 1;
        }
    }

    return assignment;
}

// 计算欧氏距离
float euclideanDistance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

// 使用匈牙利算法进行数据关联，返回关联到的数据对
std::vector<std::pair<Point, Point>> associatePoints(
        const std::vector<Point>& sensor1_points,
        const std::vector<Point>& sensor2_points,
        float max_distance) {

    std::vector<std::pair<Point, Point>> matched_pairs;

    if (sensor1_points.empty() || sensor2_points.empty()) {
        return matched_pairs;
    }

    // 创建成本矩阵
    std::vector<std::vector<float>> cost_matrix(
            sensor1_points.size(),
            std::vector<float>(sensor2_points.size(), max_distance * 2));  // 初始化为最大距离的2倍

    for (size_t i = 0; i < sensor1_points.size(); ++i) {
        for (size_t j = 0; j < sensor2_points.size(); ++j) {
            float dist = euclideanDistance(sensor1_points[i], sensor2_points[j]);
            if (dist <= max_distance) {
                cost_matrix[i][j] = dist;
            }
        }
    }

    // 使用匈牙利算法求解
    HungarianAlgorithm hungarian(cost_matrix);
    std::vector<int> assignment = hungarian.solve();

    // 构建匹配结果对
    for (size_t i = 0; i < assignment.size(); ++i) {
        if (assignment[i] != -1 && cost_matrix[i][assignment[i]] <= max_distance) {
            matched_pairs.emplace_back(
                    sensor1_points[i],
                    sensor2_points[assignment[i]]
            );
        }
    }

    return matched_pairs;
}