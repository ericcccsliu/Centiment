#include "sentiment_analyzer.hpp"
#include <sstream> 
#include <iostream>

SentimentAnalyzer::SentimentAnalyzer(){
    ProcessLexicon(); 
    ProcessNegations();
    ProcessBoosterPos();
    ProcessBoosterNeg();
}

void SentimentAnalyzer::ProcessLexicon(){
    ifstream ifs("data/sentiment_lexicon.txt"); 
    string line;
    while(getline(ifs, line, '\n')){
        stringstream line_stream(line); 
        string keyword, value_string; 
        getline(line_stream, keyword, '\t'); 
        getline(line_stream, value_string, '\t');
        int value = stoi(value_string); 
        lex.insert(std::make_pair(keyword, value)); 
    }
}
void SentimentAnalyzer::ProcessNegations(){
    ifstream ifs("data/negations.txt");
    string line;
    while(getline(ifs, line)){
        negations.insert(line);
    }
}
void SentimentAnalyzer::ProcessBoosterPos(){
    ifstream ifs("data/booster_increase.txt");
    string line;
    while(getline(ifs, line)){
        booster_pos.insert(line);
    }
}
void SentimentAnalyzer::ProcessBoosterNeg(){
    ifstream ifs("data/booster_decrease.txt");
    string line;
    while(getline(ifs, line)){
        booster_neg.insert(line);
    }
}

double SentimentAnalyzer::Analyze(std::string input_dir) {
    // assuming 1 sentence input for now
    std::vector<std::string> tokens = Tokenize(input_dir);
    return 0.0;
}

std::vector<std::string> SentimentAnalyzer::Tokenize(std::string input_dir) {
    std::vector<std::string> out;
    std::ifstream ifs{input_dir};
    std::string word;
    std::string letters = "abcdefghijklmnopqrstuvwxyz";
    for (std::string line; std::getline(ifs, line);) {
        for(int i = 0; i < line.length(); i++) {
            if(letters.find(std::tolower(line[i])) != std::string::npos) {
                word+=line[i];
            } 
            else if (word.length() > 0){
                out.push_back(word);
                word = "";
            }           
        }
        if (word.length() > 0){
            out.push_back(word);
            word = "";
        }
    }
    return out;

}