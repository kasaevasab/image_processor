#pragma once

#include "bit_map.h"
#include "cmd_parser.h"
#include "filter_pipeline_factory.h"
#include "ip_exception.h"

class App {
public:
    void Run(int argc, char* argv[]);
    void FillFilterPipelineFactory();
    void ProcessIpException(const IpException& exception);

    inline static const std::string_view INFO =
        "\nInput format:\n\n"
        "image_processor {input_filename} {output_filename} [-filter [param1] [param2] ...] [-filter ...] ...\n"
        "Example: image_processor input.bmp output.bmp -neg -edge 7\n\n"
        "Available filters:\n"
        "-- GrayScale filter | -gs\n"
        "-- Negative filter | -neq\n"
        "-- Crop filter. Parameters: width, height (in pixels) - positive integers | -crop 500 400\n"
        "-- Sharpening filter | -sharp\n"
        "-- Edge detection filter. Parameters: threshold - positive integer | -edge 7\n"
        "-- Gaussian Blur filter. Parameters: sigma (blur radius) - positive integer | -blur 2\n"
        "-- Swap filter | -swap\n\n";

protected:
    CmdParser parser_;
    BitMap bmp_;
    FilterPipelineFactory pipeline_;
};

