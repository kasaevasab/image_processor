#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include "cmd_parser.h"

struct Pixel {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;

    void SetPixel(double red_, double green_, double blue_) {
        auto help_func = [](double x) { return static_cast<int8_t> (std::min(255.0, std::max(0.0, x))); };
        red = help_func(red_);
        green = help_func(green_);
        blue = help_func(blue_);
    }

    Pixel& operator=(const Pixel& other) {
        red = other.red;
        green = other.green;
        blue = other.blue;
        return *this;
    }
};

using PixelsVector = std::vector<Pixel>;

class BitMap {
public:
    struct BMPHeader {
        uint16_t signature;        // windows bmp
        uint32_t filesize;         // filesize
        uint32_t dummy;            // unused parameters
        uint32_t bitarray_offset;  // смещение, после которого начинаются пиксели
    } __attribute__((__packed__));

    struct DIBHeader {
        uint32_t header_size;
        uint32_t width;
        uint32_t height;
        uint64_t dummy1;
        uint32_t raw_data_size;
        uint64_t dummy2;
        uint64_t dummy3;
    } __attribute__((__packed__));

public:
    void FreePixelsStorage();

    void CopyIntoPixelsStorage(PixelsVector pixels, size_t height, size_t width);

    PixelsVector& GetPixels() {
        return pixels_;
    }

    const PixelsVector& GetPixels() const {
        return pixels_;
    }

    Pixel& GetPixel(size_t row, size_t column) {
        return pixels_.at(row * dib_header_.width + column);
    }

    const Pixel& GetPixel(size_t row, size_t column) const {
        return pixels_.at(row * dib_header_.width + column);
    }

    BMPHeader& GetBMPHeader() {
        return bmp_header_;
    }

    DIBHeader& GetDIBHeader() {
        return dib_header_;
    }

    size_t GetHeight() const {
        return dib_header_.height;
    }

    size_t GetWidth() const {
        return dib_header_.width;
    }

    void SetPixel(size_t row, size_t column, const Pixel& pixel) {
        pixels_[row * dib_header_.width + column] = pixel;
    }

    void SetHeight(size_t height) {
        dib_header_.height = height;
    }

    void SetWidth(size_t width) {
        dib_header_.width = width;
    }

public:
    void Load(std::string_view filename);  // loads a file by filename
    void Load(std::istream& stream);       // loads a file from a reading stream (bool / void)

    void Write(std::string_view filename);

    void Write(std::ostream& stream);

protected:
    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    PixelsVector pixels_;
};
