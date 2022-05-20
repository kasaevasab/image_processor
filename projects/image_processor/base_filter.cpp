#include "base_filter.h"
#include <math.h>

void CropFilter::Apply(BitMap& bmp) {
    if (height_ == bmp.GetHeight() && width_ == bmp.GetWidth()) {
        return;
    }
    if (height_ == bmp.GetHeight() || width_ == bmp.GetWidth()) {
        bmp.FreePixelsStorage();
        return;
    }
    height_ = height_ > bmp.GetHeight() ? bmp.GetHeight() : height_;
    width_ = width_ > bmp.GetWidth() ? bmp.GetWidth() : width_;

    PixelsVector storage(height_ * width_);
    for (size_t row = 0; row < height_; ++row) {
        for (size_t column = 0; column < width_; ++column) {
            if (row < bmp.GetHeight() && column < bmp.GetWidth()) {
                storage[row * width_ + column] = bmp.GetPixel(bmp.GetHeight() - height_ + row, column);
            }
        }
    }
    bmp.CopyIntoPixelsStorage(storage, height_, width_);
}

void GrayScaleFilter::Apply(BitMap& bmp) {
    for (Pixel& pixel : bmp.GetPixels()) {
        uint8_t pixel_value = 0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue;
        pixel.SetPixel(pixel_value, pixel_value, pixel_value);
    }
}

void NegativeFilter::Apply(BitMap& bmp) {
    for (Pixel& pixel : bmp.GetPixels()) {
        pixel.SetPixel(255 - pixel.red, 255 - pixel.green, 255 - pixel.blue);
    }
}

SharpeningFilter::SharpeningFilter() {
    matrix_ = Utils::QuadMatrix::Storage({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}});
}

void SharpeningFilter::Apply(BitMap& bmp) {
    bmp.CopyIntoPixelsStorage(matrix_.ApplyFilterMatrixToBMP(bmp), bmp.GetHeight(), bmp.GetWidth());
}

EdgeDetectionFilter::EdgeDetectionFilter(size_t threshold) : threshold_(threshold) {
    matrix_ = Utils::QuadMatrix::Storage({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}});
}

void EdgeDetectionFilter::Apply(BitMap& bmp) {
    GrayScaleFilter::Apply(bmp);
    bmp.CopyIntoPixelsStorage(matrix_.ApplyFilterMatrixToBMP(bmp), bmp.GetHeight(), bmp.GetWidth());
    for (size_t i = 0; i < bmp.GetHeight(); ++i) {
        for (size_t j = 0; j < bmp.GetWidth(); ++j) {
            Pixel& pixel = bmp.GetPixel(i, j);
            if (pixel.red > threshold_) {
                pixel.SetPixel(255, 255, 255);
            } else {
                pixel.SetPixel(0, 0, 0);
            }
        }
    }
}

double GaussianBlurFilter::GaussFunc(int i, int j, double sigma) {
    const double PI = std::atan(1) * 4;
    const double SIGQ = sigma * sigma;
    return std::exp((-i * i - j * j) / (2 * SIGQ)) / (2 * PI * SIGQ);
}

void GaussianBlurFilter::GenerateGaussianMatrix() {
    int32_t kern = 6 * ceil(sigma_) + 1;
    int32_t mid = 3 * ceil(sigma_);
    double elem_sum = 0;
    matrix_ = Utils::QuadMatrix(kern);
    std::vector<std::pair<int, int>> shifts = Utils::GetShiftsVector(kern);
    for (const std::pair<int, int>& shift : shifts) {
        int32_t i = mid + shift.first;
        int32_t j = mid + shift.second;
        double g = GaussFunc(i, j, sigma_);
        elem_sum += g;
        matrix_.GetElement(i, j) = g;
    }
    for (int32_t i = 0; i < kern; ++i) {
        for (int32_t j = 0; j < kern; ++j) {
            matrix_.GetElement(i, j) = matrix_.GetElement(i, j) / elem_sum;
        }
    }
}

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {
    GenerateGaussianMatrix();
}

void GaussianBlurFilter::Apply(BitMap& bmp) {
    bmp.CopyIntoPixelsStorage(matrix_.ApplyFilterMatrixToBMP(bmp), bmp.GetHeight(), bmp.GetWidth());
}

void SwapFilter::Apply(BitMap& bmp) {
    if (!bmp.GetWidth() || !bmp.GetHeight()) {
        return;
    }
    size_t row_div = divider_ % bmp.GetHeight();
    size_t col_div = divider_ % bmp.GetWidth();
    PixelsVector new_pixels(bmp.GetHeight() * bmp.GetWidth());
    for (size_t row = 0; row < row_div; ++row) {
        for (size_t column = 0; column < col_div; ++column) {
            new_pixels[(bmp.GetHeight() - row_div + row) * bmp.GetWidth() + bmp.GetWidth() - col_div + column] =
                bmp.GetPixel(row, column);
        }
        for (size_t column = col_div; column < bmp.GetWidth(); ++column) {
            new_pixels[(bmp.GetHeight() - row_div + row) * bmp.GetWidth() + column - col_div] =
                bmp.GetPixel(row, column);
        }
    }
    for (size_t row = row_div; row < bmp.GetHeight(); ++row) {
        for (size_t column = 0; column < col_div; ++column) {
            new_pixels[(row - row_div) * bmp.GetWidth() + bmp.GetWidth() - col_div + column] =
                bmp.GetPixel(row, column);
        }
        for (size_t column = col_div; column < bmp.GetWidth(); ++column) {
            new_pixels[(row - row_div) * bmp.GetWidth() + column - col_div] = bmp.GetPixel(row, column);
        }
    }
    bmp.GetPixels() = new_pixels;
}