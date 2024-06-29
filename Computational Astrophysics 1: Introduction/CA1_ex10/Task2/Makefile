CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lX11
TARGET = simulation
SOURCES = main.cpp initial.cpp scatter.cpp output.cpp draw.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	./$@

clean:
	rm -f $(TARGET) $(SOURCES:.cpp=.o)

.PHONY: all clean
