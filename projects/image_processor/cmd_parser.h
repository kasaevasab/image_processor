#pragma once

#include <string_view>
#include <vector>

struct FilterDescriptor {
    std::string_view filter_name;
    std::vector<std::string_view> filter_params;

    void Clear() {
        filter_params.clear();
    }
};

class CmdParser {
public:
    static const int MIN_PARAM_NUM = 3;
    static const int INPUT_FILENAME_POS = 1;
    static const int OUTPUT_FILENAME_POS = 2;

public:
    void Parse(int argc, char* argv[]);

    std::string_view GetInputFilename() const {
        return input_filename_;
    }
    std::string_view GetOutputFilename() const {
        return output_filename_;
    }

    std::vector<FilterDescriptor>& GetFiltersParams() {
        return filters_params_;
    }

protected:
    void ExtractFiltersParams(int argc, char* argv[]);

protected:
    std::string_view input_filename_;
    std::string_view output_filename_;
    std::vector<FilterDescriptor> filters_params_;
    char* argv_;
};
