#pragma once

#include "bit_map.h"
#include "utils.h"

class BaseFilter {
public:
    virtual ~BaseFilter() = default;
    virtual void Apply(BitMap& bmp) = 0;

    virtual const std::string_view& GetFilterName() const {
        return filter_name_;
    }

protected:
    std::string_view filter_name_ = "base filter name";
};

class CropFilter : public BaseFilter {
public:

    CropFilter(size_t width, size_t height) : width_(width), height_(height){};

    void Apply(BitMap& bmp) override;

    const std::string_view& GetFilterName() const override {
        return filter_name_;
    }

    size_t GetWidth() const {
        return width_;
    }

    size_t GetHeight() const {
        return height_;
    }

    void SetWidth(size_t w) {
        width_ = w;
    }

    void SetHidth(size_t h) {
        height_ = h;
    }

protected:
    size_t width_;
    size_t height_;
    std::string_view filter_name_ = "Crop";
};

class GrayScaleFilter : public BaseFilter {
public:

    void Apply(BitMap& bmp) override;

    const std::string_view& GetFilterName() const override {
        return filter_name_;
    }

protected:
    std::string_view filter_name_ = "GrayScale";
};

class NegativeFilter : public BaseFilter {
public:

    void Apply(BitMap& bmp) override;

    const std::string_view& GetFilterName() const override {
        return filter_name_;
    }

protected:
    std::string_view filter_name_ = "Negative";
};

class SharpeningFilter : public BaseFilter {
public:

    SharpeningFilter();

    void Apply(BitMap& bmp) override;

    const Utils::QuadMatrix& GetMatrix() const {
        return matrix_;
    }

    const std::string_view& GetFilterName() const override {
        return filter_name_;
    }

    void SetMatrix(Utils::QuadMatrix& matrix) {
        matrix_ = matrix;
    }

protected:
    Utils::QuadMatrix matrix_;
    std::string_view filter_name_ = "Sharpening";
};

class EdgeDetectionFilter : public GrayScaleFilter {
public:
    EdgeDetectionFilter(size_t threshold);

    void Apply(BitMap& bmp) override;

    const Utils::QuadMatrix& GetMatrix() const {
        return matrix_;
    }

    const std::string_view& GetFilterName() const override {
        return filter_name_;
    }

    size_t GetThreshold() const {
        return threshold_;
    }

    void SetThreshold(size_t threshold) {
        threshold_ = threshold;
    }

    void SetMatrix(Utils::QuadMatrix& matrix) {
        matrix_ = matrix;
    }

protected:
    Utils::QuadMatrix matrix_;
    size_t threshold_;
    std::string_view filter_name_ = "Edge Detection";
};

class GaussianBlurFilter : public BaseFilter {
public:
    void Apply(BitMap& bmp) override;

    GaussianBlurFilter(double sigma);

    const std::string_view& GetFilterName() const override {
        return filter_name_;
    }

    const Utils::QuadMatrix& GetMatrix() const {
        return matrix_;
    }

    double GetSigma() const {
        return sigma_;
    }

    void SetSigma(double sigma) {
        sigma_ = sigma;
    }

    void SetMatrix(Utils::QuadMatrix& matrix) {
        matrix_ = matrix;
    }

protected:
    void GenerateGaussianMatrix();

    double GaussFunc(int i, int j, double sigma);

    double sigma_;
    Utils::QuadMatrix matrix_;
    std::string_view filter_name_ = "Gaussian Blur";
};

class SwapFilter : public BaseFilter {
public:
    SwapFilter(size_t divider) : divider_(divider){};

    void Apply(BitMap& bmp) override;

    const std::string_view& GetFilterName() const override {
        return filter_name_;
    }

    size_t GetDivider() const {
        return divider_;
    }

    void SetDivider(size_t div) {
        divider_ = div;
    }

protected:
    size_t divider_;
    std::string_view filter_name_ = "Swap";
};
