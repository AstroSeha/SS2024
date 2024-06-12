CXX = g++
CXXFLAGS = -O2 -Wall
TARGET = main
SRCS = main.cpp
OUTPUT = results.txt
PLOT_SCRIPT = plot.gplt

all: $(TARGET) run

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)
	gnuplot $(PLOT_SCRIPT)

clean:
	rm -f $(TARGET) $(OUTPUT)
