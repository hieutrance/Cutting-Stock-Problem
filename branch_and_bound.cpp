#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// Struct để lưu thông tin về các pattern
struct Pattern {
    int large;
    int medium;
    int small;
    int waste;
};

// Hàm để tính phế liệu cho một pattern
int calculateWaste(int large, int medium, int small) {
    int totalLength = large * 260 + medium * 210 + small * 140;
    return (totalLength <= 420) ? (420 - totalLength) : std::numeric_limits<int>::max();
}

// Hàm để kiểm tra xem giải pháp hiện tại có hợp lệ không
bool isFeasible(int largeCount, int mediumCount, int smallCount, int requiredLarge, int requiredMedium, int requiredSmall) {
    return largeCount >= requiredLarge && mediumCount >= requiredMedium && smallCount >= requiredSmall;
}

// Hàm tối ưu hóa sử dụng Branch and Bound
void branchAndBound(const std::vector<Pattern>& patterns, int level, int currentRolls, 
                    int& bestRolls, std::vector<int>& bestCombination, std::vector<int>& currentCombination, 
                    int requiredLarge, int requiredMedium, int requiredSmall) {

    if (level >= patterns.size()) {
        // Tính toán số lượng mảnh vải hiện tại
        int largeCount = 0, mediumCount = 0, smallCount = 0;
        for (int i = 0; i < patterns.size(); ++i) {
            largeCount += currentCombination[i] * patterns[i].large;
            mediumCount += currentCombination[i] * patterns[i].medium;
            smallCount += currentCombination[i] * patterns[i].small;
        }

        // Kiểm tra tính khả thi và cập nhật kết quả nếu cần
        if (isFeasible(largeCount, mediumCount, smallCount, requiredLarge, requiredMedium, requiredSmall)) {
            if (currentRolls < bestRolls) {
                bestRolls = currentRolls;
                bestCombination = currentCombination;
            }
        }
        return;
    }

    // Giới hạn số lượng pattern có thể sử dụng
    for (int i = 0; i <= 100; ++i) { // Giới hạn số vòng lặp
        currentCombination[level] = i;
        branchAndBound(patterns, level + 1, currentRolls + i, bestRolls, bestCombination, currentCombination, requiredLarge, requiredMedium, requiredSmall);
    }
}

int main() {
    // Các pattern đã tìm được
    std::vector<Pattern> patterns = {
        {0, 0, 3, 0},   // Pattern 1
        {0, 1, 1, 70},  // Pattern 2
        {0, 2, 0, 0},   // Pattern 3
        {1, 0, 1, 20}   // Pattern 4
    }; 

    // Số lượng yêu cầu
    const int requiredLarge = 30;
    const int requiredMedium = 50;
    const int requiredSmall = 40;

    int bestRolls = std::numeric_limits<int>::max();
    std::vector<int> bestCombination(patterns.size(), 0);
    std::vector<int> currentCombination(patterns.size(), 0);

    branchAndBound(patterns, 0, 0, bestRolls, bestCombination, currentCombination, requiredLarge, requiredMedium, requiredSmall);

    // In ra kết quả
    std::cout << "Minimum rolls required: " << bestRolls << std::endl;
    for (size_t i = 0; i < patterns.size(); ++i) {
        if (bestCombination[i] > 0) {
            std::cout << "Pattern " << i + 1 << ": " 
                      << patterns[i].large << " large, "
                      << patterns[i].medium << " medium, "
                      << patterns[i].small << " small | waste=" 
                      << patterns[i].waste << " cm"
                      << " Used " << bestCombination[i] << " times" << std::endl;
        }
    }

    return 0;
}
