#pragma once

#include "base_filter.h"
#include "cmd_parser.h"

#include <map>


class FilterPipelineFactory {
public:
    using FilterFactory = BaseFilter* (*)(const FilterDescriptor&);
    using FiltersToMakers = std::map<std::string_view, FilterFactory>;
    using FiltersPipeline = std::vector<BaseFilter*>;

public:

    FilterFactory GetFilterFactory(std::string_view name);

    BaseFilter* CreateFilter(const FilterDescriptor& fd);

    void AddFilterMakerToMap(std::string_view name, FilterFactory factory);

    FiltersPipeline MakeFiltersPipeline(std::vector<FilterDescriptor>& descriptors);

    void ExecutePipeline(const FiltersPipeline& filters_pipeline, BitMap& bmp);

    static void DestroyFiltersPipeline(FiltersPipeline& filters_pipeline);

protected:
    FiltersToMakers filters_to_makers_;
};
