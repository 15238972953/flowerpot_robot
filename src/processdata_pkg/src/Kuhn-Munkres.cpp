#include <vector>
#include <algorithm>
#include <limits>

class HungarianAlgorithm {
public:
    HungarianAlgorithm(const std::vector<std::vector<double>>& cost_matrix) 
        : cost(cost_matrix), N(cost_matrix.size()), M(cost_matrix[0].size()) {
        u.assign(N + 1, 0);
        v.assign(M + 1, 0);
        p.assign(M + 1, 0);
        way.assign(M + 1, 0);
    }
    
    std::vector<int> solve() {
        for (int i = 1; i <= N; ++i) {
            p[0] = i;
            int j0 = 0;
            std::vector<double> minv(M + 1, std::numeric_limits<double>::max());
            std::vector<bool> used(M + 1, false);
            
            do {
                used[j0] = true;
                int i0 = p[j0], j1;
                double delta = std::numeric_limits<double>::max();
                
                for (int j = 1; j <= M; ++j) {
                    if (!used[j]) {
                        double cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
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
        
        std::vector<int> assignment(N);
        for (int j = 1; j <= M; ++j) {
            if (p[j] != 0) {
                assignment[p[j] - 1] = j - 1;
            }
        }
        
        return assignment;
    }

private:
    std::vector<std::vector<double>> cost;
    int N, M;
    std::vector<double> u, v;
    std::vector<int> p, way;
};