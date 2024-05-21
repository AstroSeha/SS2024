CXX = g++
CC = gcc
CXXFLAGS = -Wall -std=c++11
CFLAGS = -Wall
EXEC = ex05_1a
SRC = ex05_1a.cpp Xgraphics.c
LIBS = -lX11

all: $(EXEC)

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC) $(LIBS)

clean:
	rm -f $(EXEC)

.PHONY: all clean
