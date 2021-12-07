#include "sentiment_analyzer.hpp"

#include <iostream>


int main(int argc, char* argv[]) {
    if(argc != 2) {
        throw std::runtime_error("2 args needed");
    }
    //std::cout << argc << std::endl;
    // assuming 1 sentence input for now
    // TODO: handle multiple sentences
    std::string file_name = argv[1];
    //SentimentAnalyzer s; 

    //std::cout << s.Analyze(in);

    std::string line;
    std::string to_anlyze;
    std::cout << file_name << std::endl;
    ifstream myfile (file_name);
    if (myfile.is_open()) {
        SentimentAnalyzer s; 
        while ( getline (myfile,line) ) {
        //std::cout << s.Analyze(line);
            to_anlyze = line;
            std::cout << to_anlyze << std::endl;
            std::cout << "result: " << s.AnalyzeLine(to_anlyze) << std::endl;
            std::cout << std::endl; 
        }
        myfile.close();
        
    }
    
}