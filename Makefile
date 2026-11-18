CC = gcc
CFLAGS = -c -Iinclude

OBJ = main.o
BIN = appadd

all: $(BIN)

$(BIN): ${OBJ}
	@echo "Compiled $(BIN) with success"
	@$(CC) $^ -o $(BIN)

%.o: src/%.c
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@echo "Files removed"
	@rm *.o $(BIN)
