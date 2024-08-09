#include <iostream>
#include <vector>
#include <limits>

// Struct để lưu thông tin về các pattern
struct Pattern {
    int large;   // Số lượng mảnh lớn (260cm)
    int medium;  // Số lượng mảnh vừa (210cm)
    int small;   // Số lượng mảnh nhỏ (140cm)
    int waste;   // Phế liệu còn lại
};

// Hàm để tính phế liệu cho một pattern
int calculateWaste(int large, int medium, int small) {
    int totalLength = large * 260 + medium * 210 + small * 140;
    return (totalLength <= 420) ? (420 - totalLength) : std::numeric_limits<int>::max();
}

// Hàm để in thông tin về một pattern
void printPattern(const Pattern& p, int index) {
    std::cout << "Pattern " << index << ": "
              << p.large << " large, "
              << p.medium << " medium, "
              << p.small << " small | waste=" << p.waste << " cm" << std::endl;
}

int main() {
    // Các pattern đã tìm được
    std::vector<Pattern> patterns = {
        {0, 0, 3, 0}, // Pattern 1
        {0, 1, 1, 70}, // Pattern 2
        {0, 2, 0, 0}, // Pattern 3
        {1, 0, 1, 20} // Pattern 4
    };

    // Số lượng yêu cầu
    const int requiredLarge = 30;
    const int requiredMedium = 50;
    const int requiredSmall = 40;

    // Biến để lưu kết quả tốt nhất
    int minRolls = std::numeric_limits<int>::max();
    std::vector<int> bestCombination;

    // Thử tất cả các tổ hợp số lần sử dụng các pattern
    int numPatterns = patterns.size();
    for (int i = 0; i < 100; ++i) { // Giới hạn số vòng lặp
        for (int j = 0; j < 100; ++j) {
            for (int k = 0; k < 100; ++k) {
                for (int l = 0; l < 100; ++l) {
                    int largeCount = i * patterns[0].large + j * patterns[1].large + k * patterns[2].large + l * patterns[3].large;
                    int mediumCount = i * patterns[0].medium + j * patterns[1].medium + k * patterns[2].medium + l * patterns[3].medium;
                    int smallCount = i * patterns[0].small + j * patterns[1].small + k * patterns[2].small + l * patterns[3].small;
                    
                    if (largeCount >= requiredLarge && mediumCount >= requiredMedium && smallCount >= requiredSmall) {
                        int totalRolls = i + j + k + l;
                        if (totalRolls < minRolls) {
                            minRolls = totalRolls;
                            bestCombination = {i, j, k, l};
                        }
                    }
                }
            }
        }
    }

    // In ra kết quả
    std::cout << "Minimum rolls required: " << minRolls << std::endl;
    for (int i = 0; i < numPatterns; ++i) {
        if (bestCombination[i] > 0) {
            printPattern(patterns[i], i + 1);
            std::cout << "Used " << bestCombination[i] << " times" << std::endl;
        }
    }

    return 0;
}
