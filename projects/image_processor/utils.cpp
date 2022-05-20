#include "utils.h"

namespace Utils {
std::vector<std::pair<int, int>> GetShiftsVector(int n) {
    std::vector<std::pair<int, int>> shifts;
    for (int i = -(n / 2); i <= n / 2; ++i) {
        for (int j = -(n / 2); j <= n / 2; ++j) {
            shifts.push_back({i, j});
        }
    }
    return shifts;
}

bool CheckFileParamsAreDigit(const FilterDescriptor& fd) {
    for (auto el : fd.filter_params) {
        for (char x : el) {
            if (!isdigit(x)) {
                return false;
            }
        }
    }
    return true;
}

Pixel QuadMatrix::ApplyFilterMatrixToPixel(const BitMap& bmp, size_t row, size_t column,
                               const std::vector<std::pair<int, int>>& shifts) {
    double red = 0;
    double green = 0;
    double blue = 0;
    for (const std::pair<int, int>& shift : shifts) {
        double coefficient =
            (GetWeight(shift.first + (GetSize() / 2), shift.second + (GetSize() / 2)));
        size_t i = std::min(std::max(0, (static_cast<int>(row) + shift.first)), static_cast<int>(bmp.GetHeight() - 1));
        size_t j =
            std::min(std::max(0, (static_cast<int>(column) + shift.second)), static_cast<int>(bmp.GetWidth() - 1));
        red += coefficient * bmp.GetPixel(i, j).red;
        green += coefficient * bmp.GetPixel(i, j).green;
        blue += coefficient * bmp.GetPixel(i, j).blue;
    }
    Pixel pixel = Pixel();
    pixel.SetPixel(red, green, blue);
    return pixel;
}

PixelsVector QuadMatrix::ApplyFilterMatrixToBMP(const BitMap& bmp) {
    PixelsVector new_pixels = PixelsVector(bmp.GetHeight() * bmp.GetWidth());
    std::vector<std::pair<int, int>> shifts = Utils::GetShiftsVector(GetSize());
    for (size_t i = 0; i < bmp.GetHeight(); ++i) {
        for (size_t j = 0; j < bmp.GetWidth(); ++j) {
            new_pixels[i * bmp.GetWidth() + j] = ApplyFilterMatrixToPixel(bmp, i, j, shifts);
        }
    }
    return new_pixels;
}
}  // namespace Utils
