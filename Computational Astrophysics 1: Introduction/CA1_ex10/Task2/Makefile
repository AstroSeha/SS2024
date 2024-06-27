CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = output
SOURCES = main.cpp 
PLOT_SCRIPT = plot.gplt

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./$@
	gnuplot $(PLOT_SCRIPT)

clean:
	rm -f $(TARGET) $(SOURCES:.cpp=.o) results.txt

.PHONY: all clean