#include "bit_map.h"
#include "ip_exception.h"

#include <fstream>
#include <algorithm>

void BitMap::FreePixelsStorage() {
    pixels_.clear();
    dib_header_.height = 0;
    dib_header_.width = 0;
}

void BitMap::CopyIntoPixelsStorage(PixelsVector pixels, size_t height, size_t width) {
    FreePixelsStorage();
    pixels_ = pixels;
    dib_header_.height = height;
    dib_header_.width = width;
}

void BitMap::Load(std::istream& stream) {
    if (!stream || stream.eof()) {
        throw IpException(IpException::Exceptions::LoadFileError);
    }
    stream.read(reinterpret_cast<char*>(&bmp_header_), sizeof(bmp_header_));
    if (!stream || stream.eof()) {
        throw IpException(IpException::Exceptions::LoadFileError);
    }
    stream.read(reinterpret_cast<char*>(&dib_header_), sizeof(dib_header_));

    const size_t RUBBISH = (4 - (dib_header_.width * 3) % 4) % 4;

    for (size_t row = 0; row < dib_header_.height; ++row) {
        for (size_t column = 0; column < dib_header_.width; ++column) {
            Pixel pixel_help;
            if (!stream || stream.eof()) {
                throw IpException(IpException::Exceptions::LoadFileError);
            }
            stream.read(reinterpret_cast<char*>(&pixel_help), sizeof(pixel_help));
            pixels_.push_back(pixel_help);
        }
        stream.ignore(RUBBISH);
    }
}

void BitMap::Load(std::string_view filename) {
    std::fstream file;
    file.open(static_cast<std::string>(filename),
              std::ios_base::in | std::ios_base::binary);  // for reading as a binary_file;
    if (!file.is_open()) {
        throw IpException(IpException::Exceptions::LoadFileError);
    }
    Load(file);
}

void BitMap::Write(std::ostream& stream) {
    if (!stream) {
        throw IpException(IpException::Exceptions::WriteFileError);
    }
    stream.write(reinterpret_cast<char*>(&bmp_header_), sizeof(bmp_header_));
    if (!stream) {
        throw IpException(IpException::Exceptions::WriteFileError);
    }
    stream.write(reinterpret_cast<char*>(&dib_header_), sizeof(dib_header_));
    const size_t RUBBISH = (4 - (dib_header_.width * 3) % 4) % 4;
    Pixel default_pixel = Pixel();
    for (size_t row = 0; row < dib_header_.height; ++row) {
        for (size_t column = 0; column < dib_header_.width; ++column) {
            Pixel pixel_help = GetPixel(row, column);
            stream.write(reinterpret_cast<char*>(&pixel_help), sizeof(pixel_help));
        }
        for (size_t i = 0; i < RUBBISH; ++i) {
            stream.write(reinterpret_cast<char*>(&default_pixel), sizeof(default_pixel));
        }
    }
}

void BitMap::Write(std::string_view filename) {
    std::fstream file;
    file.open(static_cast<std::string>(filename), std::ios_base::out | std::ios_base::binary);
    if (!file.is_open()) {
        throw IpException(IpException::Exceptions::WriteFileError);
    }
    Write(file);
}
