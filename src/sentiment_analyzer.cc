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

double SentimentAnalyzer::AnalyzeLine(std::string input){
    std::vector<std::vector<std::string>> sentences = TokenizeString(input);

    double raw_score = 0.0; 

    for(auto sent : sentences) {
        raw_score += AnalyzeSentenceVector(sent);
    }
    return ScaleScore(raw_score); 
}

double SentimentAnalyzer::AnalyzeDirectory(std::string input_dir) {
    std::vector<std::vector<std::string>>  sentences = TokenizeDirectory(input_dir);

    double raw_score = 0.0;

    for(auto sent : sentences) {
        raw_score += AnalyzeSentenceVector(sent);
    }
    return ScaleScore(raw_score);
}

double SentimentAnalyzer::AnalyzeSentenceVector(std::vector<std::string> &sentence) const{
    double score = 0.0;
    double negation_multiplier = 1; 
    int booster_distance = 0; 
    Booster current_booster = Booster::none; 

    if(ContainsBut(sentence)){
        size_t i = 0; 
        std::vector<std::string> before_but; 
        std::vector<std::string> after_but; 
        while(sentence.at(i) != "but"){
            before_but.push_back(sentence.at(i)); 
            i++; 
        }
        i++; 
        while(i < sentence.size()){
            after_but.push_back(sentence.at(i));
            i++; 
        }
        return (weight_before_but * AnalyzeSentenceVector(before_but) + weight_after_but * AnalyzeSentenceVector(after_but)); 
    }

    for(std::string s : sentence) {
        double word_score = 0; 
        if(IsNegativeBooster(s)){
            current_booster = Booster::negative;
            booster_distance = 0; 
        } else if(IsPositiveBooster(s)){
            current_booster = Booster::positive; 
            booster_distance = 0; 
        }
        if(IsNegation(s)){
            negation_multiplier *= -1; 
        }
        if(lex.count(s) > 0){
            if(booster_distance <= 3 && current_booster != Booster::none){
                if(current_booster == Booster::positive){
                    word_score = (lex.at(s) + booster_multiplier*lex.at(s)); 
                } else {
                    word_score = (lex.at(s) - booster_multiplier*lex.at(s)); 
                }
            } else {
                word_score = lex.at(s); 
            }
        } 
      
        score += word_score; 
        
        booster_distance++; 
    }
    return score * negation_multiplier;
}

bool SentimentAnalyzer::IsPositiveBooster(std::string &word) const{
    return booster_pos.count(word) > 0; 
}
bool SentimentAnalyzer::IsNegativeBooster(std::string &word) const{
    return booster_neg.count(word) > 0; 
}

bool SentimentAnalyzer::IsNegation(std::string &word) const{
    return negations.count(word) > 0; 
}

/**
 * scales score using tanh(x)
 * ScaleScore uses this function because it approaches its upper and lower bounds 
 * "faster" than the logistic function, x/sqrt(1+x^2), 1/(1 + |x|) and (2/pi)arctan(x)
 * 
 * this is important if you want to compare scores for smaller files
 * for example, tanh(1.47) is about .90 while 1/(1+|9|) is 0.90
 * 
 * TODO: add options for scale function 
 * (i.e. x/sqrt(1+x^2), tanh(x), erf(sqrt(pi)x/2)
 * (2/pi)arctan(x))
 **/
double SentimentAnalyzer::ScaleScore(double raw_score) {
    return tanh(raw_score);
}

bool SentimentAnalyzer::ContainsBut(std::vector<std::string> &sentence) const {
    for(std::string s : sentence){
        if(s == "but"){
            return true; 
        }
    }
    return false; 
}

std::vector<std::vector<std::string>> SentimentAnalyzer::TokenizeString(std::string input){
    std::vector<std::vector<std::string>>  out;
    std::vector<std::string> sent;
    std::string word = "";

    
    for(char c : input) {
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


std::vector<std::vector<std::string>>  SentimentAnalyzer::TokenizeDirectory(std::string input_dir) {
    std::ifstream ifs{input_dir};
    std::vector<std::vector<std::string>>  out;
    std::vector<std::string> sent;
    std::string word;

    for (std::string line; std::getline(ifs, line);) {
        for(char c : line) {
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
    std::string letters = "abcdefghijklmnopqrstuvwxyz'";
    return letters.find(std::tolower(c)) != std::string::npos;
}