CXX = g++
CXXFLAGS = -std=c++11 -O2
OBJS = main.o euler.o euler_cromer.o euler_richardson.o runge_kutta4.o energy.o initial.o period.o runge_kutta4_float.o
TARGET = output

all: $(TARGET) clean_objs

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)
	make plot

plot:
	gnuplot figure.gplt

clean_objs:
	rm -f $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET) accuracy.dat accuracy_plot.png
