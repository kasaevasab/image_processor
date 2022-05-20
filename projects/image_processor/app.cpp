#include "app.h"
#include "filter_factories.h"

void App::FillFilterPipelineFactory() {
    pipeline_.AddFilterMakerToMap("gs", &FilterFactories::MakeGrayScaleFilter);
    pipeline_.AddFilterMakerToMap("neg", &FilterFactories::MakeNegativeFilter);
    pipeline_.AddFilterMakerToMap("crop", &FilterFactories::MakeCropFilter);
    pipeline_.AddFilterMakerToMap("sharp", &FilterFactories::MakeSharpeningFilter);
    pipeline_.AddFilterMakerToMap("edge", &FilterFactories::MakeEdgeDetectionFilter);
    pipeline_.AddFilterMakerToMap("blur", &FilterFactories::MakeGaussianBlurFilter);
    pipeline_.AddFilterMakerToMap("swap", &FilterFactories::MakeSwapFilter);
}

void App::ProcessIpException(const IpException& exception) {
    const IpException::Exceptions& type = exception.GetExceptionType();
    if (type == IpException::Exceptions::CmdParserError) {
        std::cerr<<"\nPlease, verify your input data accuracy\n";
        return;
    }
    if (type == IpException::Exceptions::WrongArgsError) {
        std::cerr<<"\nWrong arguments set\n";
        return;
    }
    if (type == IpException::Exceptions::FileTypeError) {
        std::cerr << "\nYour input and output files formats must be \".bmp\"\n";
        return;
    }
    if (type == IpException::Exceptions::InvalidFilterError) {
        std::cerr<<"\nPlease check, whether all of the filters you apply exist\n";
        return;
    }
    if (type == IpException::Exceptions::LoadFileError) {
        std::cerr<<"\nCouldn't load the file\n";
        return;
    }
    if (type == IpException::Exceptions::WriteFileError) {
        std::cerr << "\nCouldn't write data to the file\n";
        return;
    }
}

void App::Run(int argc, char* argv[]) {
    try {
        parser_.Parse(argc, argv);
        std::cout << "...loading file \"" << parser_.GetInputFilename() << "\"" << std::endl;
        bmp_.Load(parser_.GetInputFilename());
        std::cout << "File loaded \"" << parser_.GetInputFilename() << "\"" << std::endl;
        FilterPipelineFactory::FiltersPipeline filters_pipeline = pipeline_.MakeFiltersPipeline(parser_.GetFiltersParams());
        pipeline_.ExecutePipeline(filters_pipeline, bmp_);
        std::cout << "...shaping your filtered picture" << std::endl;
        bmp_.Write(parser_.GetOutputFilename());
        std::cout << "Your filtered picture is ready. Find it here \"" << parser_.GetOutputFilename() << "\"" << std::endl;
        FilterPipelineFactory::DestroyFiltersPipeline(filters_pipeline);
    } catch (const IpException& exception) {
        ProcessIpException(exception);
        std::cout << INFO;
    } catch (const std::exception& exception) {
        std::cerr<< "Unexpected Error: \n" << exception.what() << std::endl;
    }
}
