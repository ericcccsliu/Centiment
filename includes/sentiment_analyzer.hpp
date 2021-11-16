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
        void ProcessLexicon(); 
        void ProcessNegations();
}; 

#endif