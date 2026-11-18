CC = gcc
CFLAGS = -c -Iinclude

OBJ = main.o
BIN = appadd

all: $(BIN)

$(BIN): ${OBJ}
	$(CC) $^ -o $(BIN)

%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(BIN)
