#ifndef SENTIMENT_ANALYZER_H
#define SENTIMENT_ANALYZER_H

#include <unordered_map>
#include <string>

using namespace std; 
class SentimentAnalyzer { 
    public:
        SentimentAnalyzer(); 
    private: 
        unordered_map<string, int> lex;

        void ProcessLexicon(); 
}; 

#endif