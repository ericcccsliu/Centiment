#include "sentiment_analyzer.hpp"
#include "database_processing.hpp"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        throw std::runtime_error("2 args needed");
    }

    // assuming 1 sentence input for now
    // TODO: handle multiple sentences
    std::string input = argv[1];
    SentimentAnalyzer s; 
    // std::cout << s.Analyze(input);
}