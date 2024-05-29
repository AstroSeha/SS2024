CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lX11
TARGET = output
SOURCES = main.cpp initial.cpp euler_richardson.cpp output.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean_objects:
	rm -f $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS)
