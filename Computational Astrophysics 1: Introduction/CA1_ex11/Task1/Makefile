CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lX11
TARGET = simulation
PLOT_SCRIPT = plot.gplt
SOURCES = main.cpp initial.cpp scatter.cpp output.cpp draw.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	./$@
	gnuplot $(PLOT_SCRIPT)


clean:
	rm -f $(TARGET) $(SOURCES:.cpp=.o)

.PHONY: all clean
