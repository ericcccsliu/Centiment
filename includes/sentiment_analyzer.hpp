#ifndef SENTIMENT_ANALYZER_H
#define SENTIMENT_ANALYZER_H

#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std; 
class SentimentAnalyzer { 
    public:
        SentimentAnalyzer(); 
    private: 
        unordered_map<string, int> lex;
        unordered_set<string> negations;
        unordered_set<string> booster_pos;
        unordered_set<string> booster_neg;
        void ProcessLexicon(); 
        void ProcessNegations();
        void ProcessBoosterPos();
        void ProcessBoosterNeg();
}; 

#endif