# Makefile for compiling and plotting harmonic oscillator

CXX = g++
CXXFLAGS = -O2 -Wall
TARGET = ex05_1a

all: $(TARGET) plot

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp

plot: $(TARGET)
	./$(TARGET)
	gnuplot ex05_1a.gplt

clean:
	rm -f $(TARGET) ex05_1a_euler.dat ex05_1a_analytic.dat ex05_1a.png
