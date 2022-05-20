#pragma once

#include "base_filter.h"

namespace FilterFactories {

BaseFilter* MakeCropFilter(const FilterDescriptor& fd);
BaseFilter* MakeGrayScaleFilter(const FilterDescriptor& fd);
BaseFilter* MakeNegativeFilter(const FilterDescriptor& fd);
BaseFilter* MakeSharpeningFilter(const FilterDescriptor& fd);
BaseFilter* MakeEdgeDetectionFilter(const FilterDescriptor& fd);
BaseFilter* MakeGaussianBlurFilter(const FilterDescriptor& fd);
BaseFilter* MakeSwapFilter(const FilterDescriptor& fd);

}  // namespace FilterFactories