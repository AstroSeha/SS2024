CC = gcc
CFLAGS = -Wall -std=c11
EXEC = ex05_1a
SRC = ex05_1a.c Xgraphics.c
LIBS = -lX11

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LIBS)

clean:
	rm -f $(EXEC)

.PHONY: all clean
