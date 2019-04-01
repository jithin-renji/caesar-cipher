CC = gcc
CFLAGS = -Wall -g

BIN = caesar
SRC = main.c

$(BIN): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(BIN)

install: $(BIN)
	@cp -f $(BIN) /usr/bin
	@echo "Done!"
