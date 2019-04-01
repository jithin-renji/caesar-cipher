CC = gcc
CFLAGS = -Wall -g

BIN = caesar
SRC = main.c

$(BIN): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(BIN)