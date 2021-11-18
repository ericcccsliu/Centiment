#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include "sentiment_analyzer.hpp"

TEST_CASE("Tokenize", "") {
    SentimentAnalyzer s;
    std::vector<std::string> in = s.Tokenize("./tests/test_input.txt");
    REQUIRE(in.size() == 2);
    REQUIRE(in[0] == "hello");
    REQUIRE(in[1] == "world");

    std::vector<std::string> in1 = s.Tokenize("./tests/test_input_1.txt");
    REQUIRE(in1.size() == 6);
    REQUIRE(in1[0] == "hello");
    REQUIRE(in1[1] == "world");
    REQUIRE(in1[2] == "hello");
    REQUIRE(in1[3] == "world");
    REQUIRE(in1[4] == "hello");
    REQUIRE(in1[5] == "world");
}