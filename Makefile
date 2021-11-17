CXX=clang++
INCLUDES=-Iincludes/ -Ilib/ -Iutilities/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++20 -g -fstandalone-debug

exec: bin/exec
tests: bin/tests
process: bin/process

bin/exec: ./src/main.cc ./src/sentiment_analyzer.cc
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o $@

bin/tests: ./tests/tests.cc obj/catch.o ./src/sentiment_analyzer.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

bin/process: ./database_processing/main.cc ./database_processing/database_processing.cc
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o $@

obj/catch.o: tests/catch.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/* obj/*