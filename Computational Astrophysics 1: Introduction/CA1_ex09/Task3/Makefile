CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = output
SOURCES = main.cpp 

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./$@

clean:
	rm -f $(TARGET) $(SOURCES:.cpp=.o) 

.PHONY: all clean