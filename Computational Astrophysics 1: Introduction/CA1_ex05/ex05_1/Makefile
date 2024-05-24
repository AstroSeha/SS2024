CXX = g++
CXXFLAGS = -O2 -Wall
TARGET1 = ex05_1a
TARGET2 = ex05_1b
TARGET3 = ex05_1c


all: $(TARGET1) $(TARGET2) $(TARGET3) plot

$(TARGET1): $(TARGET1).cpp
	$(CXX) $(CXXFLAGS) -o output_1a $(TARGET1).cpp

$(TARGET2): $(TARGET2).cpp
	$(CXX) $(CXXFLAGS) -o output_1b $(TARGET2).cpp

$(TARGET3): $(TARGET3).cpp
	$(CXX) $(CXXFLAGS) -o output_1c $(TARGET3).cpp

plot: $(TARGET1) $(TARGET2) $(TARGET3)
	./output_1a
	./output_1b
	./output_1c
	gnuplot ex05_1a.gplt
	gnuplot ex05_1b.gplt
	gnuplot ex05_1c.gplt

clean:
	rm -f output_1a output_1b output_1c ex05_1a_euler.dat ex05_1a_analytic.dat ex05_1b_euler.dat ex05_1b_analytic.dat ex05_1c_euler_cromer.dat ex05_1c_analytic.dat ex05_1a.png ex05_1b.png ex05_1c.png
