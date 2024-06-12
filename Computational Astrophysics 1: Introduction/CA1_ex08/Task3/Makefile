CXX = g++
CXXFLAGS = -O2 -Wall
TARGET = output
SOURCES = main.cpp ode_euler.cpp shooting.cpp
PLOT_SCRIPT = plot.gplt

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./$@
	gnuplot $(PLOT_SCRIPT)

clean:
	rm -f $(TARGET) $(SOURCES:.cpp=.o)

.PHONY: all clean