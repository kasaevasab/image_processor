#include "filter_factories.h"
#include "ip_exception.h"

namespace FilterFactories {

BaseFilter* MakeGrayScaleFilter(const FilterDescriptor& fd) {
    if (!fd.filter_params.empty() || fd.filter_name != "gs") {
        throw IpException(IpException::Exceptions::WrongArgsError);
    }
    return new GrayScaleFilter;
}

BaseFilter* MakeNegativeFilter(const FilterDescriptor& fd) {
    if (!fd.filter_params.empty() || fd.filter_name != "neg") {
        throw IpException(IpException::Exceptions::WrongArgsError);
    }
    return new NegativeFilter;
}

BaseFilter* MakeCropFilter(const FilterDescriptor& fd) {
    if (fd.filter_params.size() != 2 || fd.filter_name != "crop" || !Utils::CheckFileParamsAreDigit(fd)) {
        throw IpException(IpException::Exceptions::WrongArgsError);
    }
    BaseFilter* crop = new CropFilter(stoi((static_cast<std::string>(fd.filter_params[0]))),
                                      stoi((static_cast<std::string>(fd.filter_params[1]))));
    return crop;
}

BaseFilter* MakeSharpeningFilter(const FilterDescriptor& fd) {
    if (!fd.filter_params.empty() || fd.filter_name != "sharp") {
        throw IpException(IpException::Exceptions::WrongArgsError);
    }
    return new SharpeningFilter;
}

BaseFilter* MakeEdgeDetectionFilter(const FilterDescriptor& fd) {
    if (fd.filter_params.size() != 1 || fd.filter_name != "edge" || !Utils::CheckFileParamsAreDigit(fd)) {
        throw IpException(IpException::Exceptions::WrongArgsError);
    }
    return new EdgeDetectionFilter(stoi(static_cast<std::string>(fd.filter_params[0])));
}

BaseFilter* MakeGaussianBlurFilter(const FilterDescriptor& fd) {
    if (fd.filter_params.size() != 1 || fd.filter_name != "blur") {
        throw IpException(IpException::Exceptions::WrongArgsError);
    }
    float sigma = 0;
    try {
        std::string p = static_cast<std::string>(fd.filter_params[0]);
        sigma = std::stod(p);
    } catch (std::exception& error){
        throw IpException(IpException::Exceptions::WrongArgsError);
    }
    return new GaussianBlurFilter(sigma);
}

BaseFilter* MakeSwapFilter(const FilterDescriptor& fd) {
    if (fd.filter_params.size() != 1 || fd.filter_name != "swap" || !Utils::CheckFileParamsAreDigit(fd)) {
        throw IpException(IpException::Exceptions::WrongArgsError);
    }
    return new SwapFilter(stoi(static_cast<std::string>(fd.filter_params[0])));
}

}  // namespace FilterFactories