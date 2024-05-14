# Define the compiler
CXX = g++
# Define the compiler flags
CXXFLAGS = -Wall -g

# Default target
all: output1 output2 output3

# Rule for first executable
output1: ex3_1.cpp
	$(CXX) $(CXXFLAGS) ex3_1.cpp -o output1

# Rule for second executable
output2: ex3_2.cpp
	$(CXX) $(CXXFLAGS) ex3_2.cpp -o output2

# Rule for third executable
output3: ex3_3.cpp
	$(CXX) $(CXXFLAGS) ex3_3.cpp -o output3

# Clean up
clean:
	rm -f output1 output2 output3

.PHONY: all clean

