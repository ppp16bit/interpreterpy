CC = gcc
CFLAGS = -Wall -Wextra -g3 -I.
TARGET = output/lilpython.exe
SRC = lexer.c parser.c interpreter.c main.c
OBJ = $(addprefix output/,$(SRC:.c=.o))

# Ensure output directory exists
$(shell mkdir -p output)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

output/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q output\* 2>nul

run: $(TARGET)
	.\$(TARGET)

.PHONY: all clean run