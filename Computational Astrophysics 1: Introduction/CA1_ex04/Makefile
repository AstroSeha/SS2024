CXX = g++

CXXFLAGS = -std=c++11

TARGETS = output1 output2 output4
SOURCES = ex4_1.cpp ex4_2.cpp ex4_4.cpp

all: $(TARGETS)


output1: ex4_1.cpp
	$(CXX) -o $@ $<

output2: ex4_2.cpp
	$(CXX) -o $@ $<

output4: ex4_4.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

.PHONY: all clean
