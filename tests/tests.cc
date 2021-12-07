#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include "sentiment_analyzer.hpp"

TEST_CASE("Tokenize", "") {
    SentimentAnalyzer s;
    std::vector<std::vector<std::string>> in = s.TokenizeDirectory("./tests/test_input.txt");
    REQUIRE(in.size() == 1);
    REQUIRE(in[0].size() == 2);
    REQUIRE(in[0][0] == "hello");
    REQUIRE(in[0][1] == "world");

    std::vector<std::vector<std::string>> in1 = s.TokenizeDirectory("./tests/test_input_1.txt");
    REQUIRE(in1[0].size() == 6);
    REQUIRE(in1[0][0] == "hello");
    REQUIRE(in1[0][1] == "world");
    REQUIRE(in1[0][2] == "hello");
    REQUIRE(in1[0][3] == "world");
    REQUIRE(in1[0][4] == "hello");
    REQUIRE(in1[0][5] == "world");
    
    std::vector<std::vector<std::string>> in2 = s.TokenizeDirectory("./tests/test_input_2.txt");
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

TEST_CASE("tokenize problems", "") {
    SentimentAnalyzer s;
    std::vector<std::vector<std::string>> in = s.TokenizeDirectory("./tests/test_input_4.txt");

    REQUIRE(in.size() == 2);
    REQUIRE(in[0].size() == 4);
    REQUIRE(in[1].size() == 3);
    REQUIRE(in[0][0] == "Spring");
    REQUIRE(in[0][1] == "is");
    REQUIRE(in[0][2] == "really");
    REQUIRE(in[0][3] == "here");
    REQUIRE(in[1][0] == "Swans");
    REQUIRE(in[1][1] == "are");
    REQUIRE(in[1][2] == "back");
}

TEST_CASE("tokenize string problems", "") {
    SentimentAnalyzer s;
    std::vector<std::vector<std::string>> in = s.TokenizeString("Spring is really here. Swans are back.");

    REQUIRE(in.size() == 2);
    REQUIRE(in[0].size() == 4);
    REQUIRE(in[1].size() == 3);
    REQUIRE(in[0][0] == "Spring");
    REQUIRE(in[0][1] == "is");
    REQUIRE(in[0][2] == "really");
    REQUIRE(in[0][3] == "here");
    REQUIRE(in[1][0] == "Swans");
    REQUIRE(in[1][1] == "are");
    REQUIRE(in[1][2] == "back");

    SentimentAnalyzer s1;
    std::vector<std::vector<std::string>> in1 = s1.TokenizeString("I am happy");

    REQUIRE(in1.size() == 1);
    REQUIRE(in1[0].size() == 3);
    REQUIRE(in1[0][0] == "I");
    REQUIRE(in1[0][1] == "am");
    REQUIRE(in1[0][2] == "happy");
}

TEST_CASE("Analyze", "") {
    SentimentAnalyzer s;
    REQUIRE(s.AnalyzeDirectory("./tests/test_input_3.txt") == tanh(3));
    REQUIRE(s.AnalyzeLine("I am happy") == tanh(1));
    REQUIRE(s.AnalyzeLine("I am not happy") == tanh(-1));
    REQUIRE(s.AnalyzeLine("I am terrible") == tanh(-1));
    REQUIRE(s.AnalyzeLine("I am not terrible") == tanh(1));
    bool res = s.AnalyzeLine("I am happy") < s.AnalyzeLine("I am very happy");
    REQUIRE( res == 1);
    bool res1 = s.AnalyzeLine("I am happy") > s.AnalyzeLine("I am not very happy");
    REQUIRE( res1 == 1);
}



