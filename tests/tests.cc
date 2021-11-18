#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include "sentiment_analyzer.hpp"

TEST_CASE("Tokenize", "") {
    SentimentAnalyzer s;
    std::vector<std::vector<std::string>> in = s.Tokenize("./tests/test_input.txt");
    REQUIRE(in.size() == 1);
    REQUIRE(in[0].size() == 2);
    REQUIRE(in[0][0] == "hello");
    REQUIRE(in[0][1] == "world");

    std::vector<std::vector<std::string>> in1 = s.Tokenize("./tests/test_input_1.txt");
    REQUIRE(in1[0].size() == 6);
    REQUIRE(in1[0][0] == "hello");
    REQUIRE(in1[0][1] == "world");
    REQUIRE(in1[0][2] == "hello");
    REQUIRE(in1[0][3] == "world");
    REQUIRE(in1[0][4] == "hello");
    REQUIRE(in1[0][5] == "world");
    
    std::vector<std::vector<std::string>> in2 = s.Tokenize("./tests/test_input_2.txt");
    REQUIRE(in2.size() == 3);
    // REQUIRE(in2[0].size() == 2);
    REQUIRE(in2[0][0] == "hello");
    for(auto a : in2) {
        for(auto b : a) {
            std::cout << b;
        }
        std::cout << std::endl;
    }
    std::cout << in2[0][0] << std::endl;
    std::cout << in2[1][0] << std::endl;
    std::cout << in2[2][0] << std::endl;
    REQUIRE(in2[0][1] == "world");
    REQUIRE(in2[1][0] == "hello");
    REQUIRE(in2[1][1] == "world");
    REQUIRE(in2[2][0] == "hello");
    REQUIRE(in2[2][1] == "world");

}

TEST_CASE("Analyze", "") {
    SentimentAnalyzer s;
    REQUIRE(s.Analyze("./tests/test_input_3.txt") == 3);
}