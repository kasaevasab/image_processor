#include "cmd_parser.h"
#include "ip_exception.h"

#include <string_view>

void CmdParser::ExtractFiltersParams(int argc, char* argv[]) {
    FilterDescriptor cur_filter = FilterDescriptor();
    for (auto it = argv + 3; it < argv + argc; ++it) {
        std::string_view cur_str = *it;
        if (cur_str.at(0) == '-') {
            if (it != argv + 3) {
                filters_params_.push_back(cur_filter);
                cur_filter.Clear();
            }
            cur_filter.filter_name = cur_str.substr(1, cur_str.size() - 1);
        } else if (cur_filter.filter_name != "") {
            cur_filter.filter_params.push_back(cur_str);
        } else {
            throw IpException(IpException::Exceptions::CmdParserError);
        }
    }
    filters_params_.push_back(cur_filter);
}

void CmdParser::Parse(int argc, char* argv[]) {
    if (argc < MIN_PARAM_NUM) {
        throw IpException(IpException::Exceptions::CmdParserError);
    }
    input_filename_ = argv[INPUT_FILENAME_POS];
    output_filename_ = argv[OUTPUT_FILENAME_POS];
    if (input_filename_.length() <= 4 || input_filename_.substr(input_filename_.length() - 4, 4) != ".bmp" ||
        output_filename_.length() <= 4 || output_filename_.substr(output_filename_.length() - 4, 4) != ".bmp") {
        throw IpException(IpException::Exceptions::FileTypeError);
    }
    ExtractFiltersParams(argc, argv);
}

/*
{имя программы} {путь к входному файлу} {путь к выходному файлу}
[-{имя фильтра 1} [параметр фильтра 1] [параметр фильтра 2] ...]
[-{имя фильтра 2} [параметр фильтра 1] [параметр фильтра 2] ...] ...
 */