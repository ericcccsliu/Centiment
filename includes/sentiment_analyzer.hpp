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

enum class Booster {none, positive, negative};

using namespace std; 
class SentimentAnalyzer { 
    public:
        SentimentAnalyzer();
        double AnalyzeDirectory(std::string input_dir);
        double AnalyzeLine(std::string input);
        std::vector<std::vector<std::string>> TokenizeDirectory(std::string input_dir);
        std::vector<std::vector<std::string>> TokenizeString(std::string input);
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
        double AnalyzeSentenceVector(std::vector<std::string> &sentence) const;
        bool IsPositiveBooster(std::string &word) const; 
        bool IsNegativeBooster(std::string &word) const; 
        bool IsNegation(std::string &word) const; 
        double ScaleScore(int raw_score);

        const double booster_multiplier = 0.3;
        
}; 

#endif