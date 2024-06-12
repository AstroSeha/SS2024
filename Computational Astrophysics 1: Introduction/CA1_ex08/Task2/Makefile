CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = output
SOURCES = main.cpp gauss_legendre.cpp gauss_chebyshev.cpp romberg.cpp simpson.cpp trapezoid.cpp
PLOT_SCRIPT = plot.gplt plot2.gplt

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./$@
	gnuplot $(PLOT_SCRIPT)

clean:
	rm -f $(TARGET) $(SOURCES:.cpp=.o)

.PHONY: all clean