#include "save_file.h"

// 简单的追加函数 - 一个API搞定
void appendPoint(const std::string& filename, double lat, double lon) {
    std::ofstream file;
    file.open(filename, std::ios::app);  // ios::app 表示追加模式
    
    if (file.is_open()) {
        file << std::fixed << std::setprecision(10)
             << "[" << lat << ", " << lon << "]" << std::endl;
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}

// 使用示例
// appendPoint("gps_data.txt", -22.033794403076172, 41.66986846823828);
// appendPoint("gps_data.txt", -22.033795, 41.669869);