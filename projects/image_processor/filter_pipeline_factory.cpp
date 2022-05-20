#include "filter_factories.h"
#include "filter_pipeline_factory.h"
#include "ip_exception.h"

#include <iostream>

void FilterPipelineFactory::AddFilterMakerToMap(std::string_view name, FilterFactory factory) {
    filters_to_makers_[name] = factory;
}

FilterPipelineFactory::FilterFactory FilterPipelineFactory::GetFilterFactory(std::string_view name) {
    if (filters_to_makers_.find(name) != filters_to_makers_.end()) {
        return filters_to_makers_[name];
    }
    return nullptr;
}

BaseFilter* FilterPipelineFactory::CreateFilter(const FilterDescriptor& fd) {
    FilterFactory help = GetFilterFactory(fd.filter_name);
    if (!help) {
        return nullptr;
    }
    BaseFilter* current_filter = help(fd);
    return current_filter;
}

FilterPipelineFactory::FiltersPipeline FilterPipelineFactory::MakeFiltersPipeline(
    std::vector<FilterDescriptor>& descriptors) {
    FiltersPipeline filters_pipeline;
    for (size_t i = 0; i < descriptors.size(); ++i) {
        if (filters_to_makers_.find(descriptors[i].filter_name) != filters_to_makers_.end()) {
            filters_pipeline.push_back(CreateFilter(descriptors[i]));
        } else {
            throw IpException(IpException::Exceptions::InvalidFilterError);
        }
    }
    return filters_pipeline;
}

void FilterPipelineFactory::ExecutePipeline(const FiltersPipeline& filters_pipeline, BitMap& bmp) {
    for (auto el : filters_pipeline) {
        std::cout << "...applying " << el->GetFilterName() << " filter" << std::endl;
        el->Apply(bmp);
    }
}

void FilterPipelineFactory::DestroyFiltersPipeline(FiltersPipeline& filters_pipeline) {
    for (auto el : filters_pipeline) {
        delete el;
    }
}
