PROJECT = ex05_1a
OBJECTS = $(PROJECT).o Xgraphics.o

CXX = g++
CC = gcc
CXXFLAGS = -Wall
CPPLIBS = -lX11
CPPFLAGS = -I/opt/X11/include
LDFLAGS = -L/opt/X11/lib

.PHONY : clean

$(PROJECT) : $(OBJECTS)
	@echo Link project $(@)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(OBJECTS) $(CPPLIBS)

.cpp.o : 
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $<

.c.o : 
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c $<

clean :
	rm -f $(OBJECTS)
	rm -f $(PROJECT)
