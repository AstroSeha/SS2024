CXX = g++
CXXFLAGS = -O2 -std=c++11

all: output run

output: main.cpp
	$(CXX) $(CXXFLAGS) -o output main.cpp

run: output
	./output
	gnuplot figure.gplt

clean:
	rm -f output 
