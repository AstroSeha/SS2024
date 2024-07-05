CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = simulation
PLOT_SCRIPT = plot.gplt
SOURCES = main.cpp initial.cpp scatter.cpp output.cpp 

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	./$@
	gnuplot $(PLOT_SCRIPT)


clean:
	rm -f $(TARGET) $(SOURCES:.cpp=.o) results.txt task1.png

.PHONY: all clean
