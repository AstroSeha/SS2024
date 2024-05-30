CXX = g++
CXXFLAGS = -std=c++11 -O2
OBJS = main.o
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
	gnuplot figure2.gplt

clean_objs:
	rm -f $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET) trajectories.txt 
