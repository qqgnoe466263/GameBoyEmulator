#!Makefile

CC = gcc
C_FILES = $(wildcard *.c)
OBJ_FILES = $(C_FILES:%.c=%.o)
CFLAGS = -g

BIN = gb_emu

$(BIN): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<

test: $(BIN)
	./$(BIN) test/mario.gb

clean:
	rm *.o
	rm gb_emu
