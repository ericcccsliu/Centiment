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
    std::vector<std::vector<std::string>>  sentences = Tokenize(input_dir);

    int raw_score = 0;

    for(auto sent : sentences) {
        raw_score += AnalyzeSentence(sent);
    }

    return ScaleScore(raw_score);
}

int SentimentAnalyzer::AnalyzeSentence(std::vector<std::string> &sentence) const{
    int score = 0.0;
    for(std::string s : sentence) {
        if(lex.count(s) > 0){
            score += lex.at(s); 
        }
    }
    return score;
}

int SentimentAnalyzer::BoosterScore(std::vector<std::string> &sentence) const{
    /*todo*/ 
}

int SentimentAnalyzer::Negate(std::vector<std::string> &sentence) const{
    /*todo*/
    //returns +1 if there is an even number of negations
    //returns -1 if there is an odd number of negations 
}

/**
 * scales score using 1/(1+|x|)
 * ScaleScore uses this function because it approaches its upper and lower bounds 
 * "slower" than the logistic function, x/sqrt(1+x^2), tanh(x), and (2/pi)arctan(x)
 * 
 * this is important if you want to compare scores for larger, v + or v - files
 * for example, tanh(1.47) is about .90 while 1/(1+|9|) is 0.90
 * 
 * TODO: add options for scale function (i.e. x/sqrt(1+x^2), tanh(x), erf(sqrt(pi)x/2)
 * (2/pi)arctan(x))
 **/
double SentimentAnalyzer::ScaleScore(int raw_score) {
    return ((double) raw_score) / (1 + abs(raw_score));
}

std::vector<std::vector<std::string>>  SentimentAnalyzer::Tokenize(std::string input_dir) {
    std::ifstream ifs{input_dir};
    std::vector<std::vector<std::string>>  out;
    std::vector<std::string> sent;
    std::string word;

    for (std::string line; std::getline(ifs, line);) {
        for( auto c : line) {
            if(IsLetter(c)) {
                word+= c;
            }
            else if(IsSentEnd(c) && sent.size() > 0) {
                
                if(word.length() > 0) {
                    sent.push_back(word);
                    word = "";
                }
                std::vector<std::string> new_sent(sent);
                out.push_back(new_sent);
                sent = {};
            }
            else if(word.length() > 0) {
                sent.push_back(word);
                word = "";
            }
        }
        if(word.length() > 0) {
            sent.push_back(word);
             word = "";
        }

    }
    if(sent.size() > 0) {
        if(word.length() > 0) {
            sent.push_back(word);
            word = "";
        }
        std::vector<std::string> new_sent(sent);
        out.push_back(new_sent);
        sent = {};
    }
    return out;

}

bool SentimentAnalyzer::IsSentEnd(char c) {
    std::string punct = "!?.";
    return punct.find(c) != std::string::npos;
}

bool SentimentAnalyzer::IsLetter(char c) {
    std::string letters = "abcdefghijklmnopqrstuvwxyz";
    return letters.find(std::tolower(c)) != std::string::npos;
}