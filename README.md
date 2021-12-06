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

## Library
[Credit](https://iq.opengenus.org/create-shared-library-in-cpp/)
1. Copy sentiment_analyzer.so to your directory
2. Compile, create an executable

`gcc -Llib/ -Wall -o {exec name} {source file} -llibrary`

3. Set the library path

`export LD_LIBRARY_PATH={library_path}/:$LD_LIBRARY_PATH`

# Running the test suite

1. Compile 

`make tests`

2. Run

`./bin/tests`
