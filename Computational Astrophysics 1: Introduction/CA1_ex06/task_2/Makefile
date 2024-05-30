CXX = g++
CXXFLAGS = -std=c++11 -O2

TARGET = output
SOURCES = main.cpp initial.cpp euler_richardson.cpp perihelion_aphelion.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean_objects:
	rm -f $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS) $(filter-out peri_ap_log.txt, $(wildcard *.txt))



