# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Target executables
TARGET1 = output2
TARGET2 = output4

# Source files
SRCS1 = ex2_2a.C
SRCS2 = ex2_4.cpp

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(SRCS1)
	$(CXX) $(CXXFLAGS) -o $(TARGET1) $(SRCS1)

$(TARGET2): $(SRCS2)
	$(CXX) $(CXXFLAGS) -o $(TARGET2) $(SRCS2)

clean:
	rm -f $(TARGET1) $(TARGET2)

