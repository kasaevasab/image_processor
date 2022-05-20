#pragma once

#include "bit_map.h"

namespace Utils {

class QuadMatrix {
public:
    using Storage = std::vector<std::vector<double>>;

    QuadMatrix(const Storage& matrix) : matrix_(matrix){};

    QuadMatrix(size_t n) : matrix_(std::vector<std::vector<double>>(n, std::vector<double>(n))){};

    QuadMatrix() : QuadMatrix(0){};

    Pixel ApplyFilterMatrixToPixel(const BitMap& bmp, size_t row, size_t column,
                                   const std::vector<std::pair<int, int>>& shifts);

    PixelsVector ApplyFilterMatrixToBMP(const BitMap& bmp);

    size_t GetSize() const {
        return matrix_.size();
    }

    double GetWeight(size_t row, size_t column) const {
        return matrix_[row][column];
    }

    double& GetElement(size_t row, size_t column) {
        return matrix_[row][column];
    }

    const double& GetElement(size_t row, size_t column) const {
        return matrix_[row][column];
    }

protected:
    Storage matrix_;
};

std::vector<std::pair<int, int>> GetShiftsVector(int n);

bool CheckFileParamsAreDigit(const FilterDescriptor& fd);
}// namespace Utils