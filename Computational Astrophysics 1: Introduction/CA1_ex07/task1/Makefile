CXX = g++
CXXFLAGS = -O2 -std=c++11

all: output run

output: main.cpp
	$(CXX) $(CXXFLAGS) -o output main.cpp

run: output
	./output
	gnuplot figure.gplt
	gnuplot figure2.gplt

clean:
	rm -f output 
