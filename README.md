# About this project

This is a C++ library for sentiment analysis. It utilizes the positive and negative sentiment scores listed in the [NRC Word-Emotion Association Lexicon](https://saifmohammad.com/WebPages/NRC-Emotion-Lexicon.htm), as well as three additional heuristics, to assign a sentiment score to inputted text. 

## Lexicon

The sentiment lexicon that this project utilizes is an adbridged version of the NRC Word-Emotion Association Lexicon. It contains the sum of the positive and negative sentiment scores for each word. 

## Heuristics

Three heuristics are utilized to present a more accurate representation of sentiment. Some of these heuristics were inspired by/derived from the [VADER sentiment analysis](https://github.com/cjhutto/vaderSentiment) tools written in Python. They are as follows: 

### 1. Negation handling 

Our library performs negation handling at the clause level, with one exception in "but" handling. Each negation found within a sentence will multiply the resultant score of the entire clause by -1. 

### 2. Boosters

Some words in the English language increase the intensity of words that follow, and some words do the opposite, decreasing the intensity of following words. Using [VADER](https://github.com/cjhutto/vaderSentiment) as a guide, we've curated lists of words that increase and decrease intensity of words that follow. For simplicity, we refer to such words as "boosters". Our library processes boosters by increasing or reducing the sentiment scores of the three subsequent words by a empirically-derived value.  

### 3. "But"

Presence of the word "but" in a sentence causes a shift in intensity to the clause that follows after the "but". For example, the sentence
`they willingly confessed, but it wasn't the truth`
starts out as positive, but shifts to negative after the "but". However, the words that follow the "but" carry more weight, so the sentence is negative overall. To accurately analyze these sentences, they are broken apart into clauses before and after the "but". The clause before is given less weight and the clause after is given more. 

## Scaling

The score is scaled to a double value in [-1.0, 1.0]. This enables comparison between files of different sizes.

Scaling functions (graphed in [Desmos](https://www.desmos.com/calculator/v36irnqrwx)):

![Screen Shot 2021-12-07 at 2 09 39 PM](https://user-images.githubusercontent.com/56461226/145099533-d5cdb461-8fa1-47be-9175-e06f7644da5b.png)

Our library currently uses tanh(x). We chose tanh(x) because it's the least sensitive to changes in lower scores, as seen above. We expect users will be interested in comparing shorter or sentiment-ambigious files (lower raw scores), rather than two very positive or very negative files. A future version will allow users to choose the scaling function.

## Tokenization

# Building the project

1. Clone the repo locally

`git clone git@github.com:cs128-2021c/final-project-labgroup121.git`

2. Compile source files

`./bin/exec`

3. Compile test suite

`./bin/tests`

# Use

## Analysis

1. Create a text file with your input
2. Run 

`./bin/exec {filename.extension}`

The sentiment score is printed.

## Library Instructions
[Credit](https://iq.opengenus.org/create-shared-library-in-cpp/)
1. Copy sentiment_analyzer.so to your directory
2. Compile, create an executable

`gcc -Llib/ -Wall -o {exec name} {source file} -llibrary`

3. Set the library path

`export LD_LIBRARY_PATH={library_path}/:$LD_LIBRARY_PATH`

## Library Documentation: 

include the library header: 

`#include "sentiment_analyzer.hpp"` 

call the default constructor:

`SentimentAnalyzer s;`

to perform sentiment analysis on a string, use:

`AnalyzeLine(input)`

this function takes in a std::string as input and returns a double containing the sentiment score of the input text.

to perform sentiment analysis on a whole file containing text, use:

`AnalyzeDirectory(directory)`

this function takes in a std::string as input and returns a double containing the sentiment score of the text within the input directory.

# Running the test suite

1. Compile 

`make tests`

2. Run

`./bin/tests`

