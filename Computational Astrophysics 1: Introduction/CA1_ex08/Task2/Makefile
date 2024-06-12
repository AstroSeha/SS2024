CXX = g++
CXXFLAGS = -O2 -Wall
TARGET = main
SRCS = main.cpp
OUTPUT = results_F1.txt results_F2.txt
PLOT_SCRIPT = plot.gplt

all: $(TARGET) run

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)
	gnuplot $(PLOT_SCRIPT)

clean:
	rm -f $(TARGET) $(OUTPUT)
