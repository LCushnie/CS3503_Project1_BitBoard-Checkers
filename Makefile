CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o bitops.o checkers.o
TARGET = checkers

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c checkers.h bitops.h
bitops.o: bitops.c bitops.h
checkers.o: checkers.c checkers.h bitops.h

clean:
	rm -f $(OBJ) $(TARGET)
