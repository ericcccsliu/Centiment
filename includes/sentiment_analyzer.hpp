#ifndef SENTIMENT_ANALYZER_H
#define SENTIMENT_ANALYZER_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <cctype>
#include <cmath>

using namespace std; 
class SentimentAnalyzer { 
    public:
        SentimentAnalyzer();
        double Analyze(std::string input_dir);
        std::vector<std::vector<std::string>> Tokenize(std::string input_dir);
    private: 
        unordered_map<string, int> lex;
        unordered_set<string> negations;
        unordered_set<string> booster_pos;
        unordered_set<string> booster_neg;

        /*initialization*/
        void ProcessLexicon(); 
        void ProcessNegations();
        void ProcessBoosterPos();
        void ProcessBoosterNeg();

        /*processing*/ 
        bool IsSentEnd(char c);
        bool IsLetter(char c);
        int AnalyzeSentence(std::vector<std::string> &sentence) const;
        int BoosterScore(std::vector<std::string> &sentence) const; 
        int Negate(std::vector<std::string> &sentence) const; 
        double ScaleScore(int raw_score);
        
}; 

#endif