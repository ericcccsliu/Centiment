#include <fstream>
#include <string>
#include <sstream> 
#include <vector>
#include <stdexcept>

using namespace std; 

void ProcessFile() {
    ifstream ifs("data/full_lexicon.txt"); 
    ostream ofs("data/sentiment_lexicon.txt")
    while(ifs.good()){
        string discard; 
        string negative_string;
        string positive_string; 
        for(int i = 0; i < 10; i++){
            if(i == 5){
                getline(ifs, negative_string); 
            } else if (i == 6) {
                getline(ifs, positive_string); 
            } else {
                getline(ifs, discard); 
            }
        }
        stringstream negative_stream(negative_string);
        stringstream positive_stream(positive_string);

        vector<string> negative_vect(3); 
        vector<string> positive_vect(3);

        for(int i = 0; i < 3; i++){
            getline(negative_stream, negative_vect.at(i), ' ');
            getline(positive_stream, positive_vect.at(i), ' ');
        }

        if(negative_vect.at(0) != positive_vect.at(0)) throw runtime_error("negative and positive strings don't match up"); 

        string current_word = negative_vect.at(0); 

        int sentiment = (-1 * stoi(negative_vect.at(2))) + stoi(positive_vect.at(2)); 
        ofs << current_word << " " << sentiment << std::endl; 
    }
}