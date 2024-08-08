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
    const int max_large = 2; // Max số lượng mảnh lớn thử nghiệm
    const int max_medium = 2; // Max số lượng mảnh vừa thử nghiệm
    const int max_small = 3; // Max số lượng mảnh nhỏ thử nghiệm

    std::vector<Pattern> patterns;

    // Thử tất cả các tổ hợp mảnh lớn, vừa, nhỏ
    for (int large = 0; large <= max_large; ++large) {
        for (int medium = 0; medium <= max_medium; ++medium) {
            for (int small = 0; small <= max_small; ++small) {
                int waste = calculateWaste(large, medium, small);
                if (waste < 140) { // Chỉ lưu pattern có phế liệu nhỏ hơn 140 cm
                    patterns.push_back({large, medium, small, waste});
                }
            }
        }
    }

    // In ra tất cả các pattern đã tìm thấy
    int index = 1;
    for (const auto& pattern : patterns) {
        printPattern(pattern, index++);
    }

    return 0;
}
