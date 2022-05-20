#include "app.h"


int main(int argc, char* argv[]) {
    App app;
    app.FillFilterPipelineFactory();
    app.Run(argc, argv);
    return 0;
}
