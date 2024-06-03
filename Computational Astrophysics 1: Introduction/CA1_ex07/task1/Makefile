CXX = g++
CXXFLAGS = -O2 -std=c++11

all: output plot

output: main.cpp
	$(CXX) $(CXXFLAGS) -o output main.cpp

run: output
	./output
	gnuplot plot.gplt

clean:
	rm -f output *.o