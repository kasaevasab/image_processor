#include <catch.hpp>

#include "app.h"
#include <string>

TEST_CASE("Successful cmd_parsing") {
    char* argv1[] = {
        const_cast<char*>("image_processor"),
        const_cast<char*>(
            "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
        const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                          "processor\\data\\output1.bmp"),
        const_cast<char*>("-blur"),
        const_cast<char*>("2"),
        const_cast<char*>("-edge"),
        const_cast<char*>("7"),
        const_cast<char*>("-swap"),
        const_cast<char*>("1024")};
    bool flag = true;
    try {
        CmdParser parser = CmdParser();
        parser.Parse(9, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Gs filter was successfully applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output1.bmp"),
            const_cast<char*>("-gs")};
        App app1 = App();
        app1.Run(4, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Gs filter was not applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output1.bmp"),
            const_cast<char*>("-gs"),
            const_cast<char*>("3")};
        App app1 = App();
        app1.Run(5, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Neg filter was successfully applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output2.bmp"),
            const_cast<char*>("-neg")};
        App app1 = App();
        app1.Run(4, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Neg filter was not applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output2.bmp"),
            const_cast<char*>("-neg"),
            const_cast<char*>("3")};
        App app1 = App();
        app1.Run(5, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Crop filter was successfully applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output3.bmp"),
            const_cast<char*>("-crop"),
            const_cast<char*>("600"),
            const_cast<char*>("800")};
        App app1 = App();
        app1.Run(6, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Crop filter was not applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output3.bmp"),
            const_cast<char*>("-crop"),
            const_cast<char*>("3")};
        App app1 = App();
        app1.Run(5, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Edge Detection filter was successfully applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output4.bmp"),
            const_cast<char*>("-edge"),
            const_cast<char*>("7")};
        App app1 = App();
        app1.Run(5, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Edge Detection filter was not applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output4.bmp"),
            const_cast<char*>("-edge")};
        App app1 = App();
        app1.Run(4, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Blur filter was successfully applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output5.bmp"),
            const_cast<char*>("-blur"),
            const_cast<char*>("2")};
        App app1 = App();
        app1.Run(5, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Blur filter was not applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output5.bmp"),
            const_cast<char*>("-blur"),
            const_cast<char*>("0ar")};
        App app1 = App();
        app1.Run(5, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Blur filter was not applied 2.0") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output5.bmp"),
            const_cast<char*>("-blur"),
            const_cast<char*>("2"),
            const_cast<char*>("3")};
        App app1 = App();
        app1.Run(5, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Swap filter was successfully applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output6.bmp"),
            const_cast<char*>("-swap"),
            const_cast<char*>("1500")};
        App app1 = App();
        app1.Run(5, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Swap filter was not applied") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output6.bmp"),
            const_cast<char*>("-swap")};
        App app1 = App();
        app1.Run(4, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("Filters were successfully applied (gs, sharp, crop)") {
    bool flag = true;
    try {
        char* argv2[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output7.bmp"),
            const_cast<char*>("-gs"),
            const_cast<char*>("-sharp"),
            const_cast<char*>("-crop"),
            const_cast<char*>("2000"),
            const_cast<char*>("1000")};
        App app2 = App();
        app2.Run(8, argv2);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("No such file") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\gi.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output1.bmp"),
            const_cast<char*>("--gs]")};
        App app1 = App();
        app1.Run(4, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}

TEST_CASE("No such filter") {
    bool flag = true;
    try {
        char* argv1[] = {
            const_cast<char*>("image_processor"),
            const_cast<char*>(
                "D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_processor\\girl.bmp"),
            const_cast<char*>("D:\\Sabina\\hse_cs\\first_course\\cpp_course\\cpp-base-hse-2022\\projects\\image_"
                              "processor\\data\\output1.bmp"),
            const_cast<char*>("-g")};
        App app1 = App();
        app1.Run(4, argv1);
    } catch (std::exception& error) {
        flag = false;
    }
    REQUIRE(flag);
}
