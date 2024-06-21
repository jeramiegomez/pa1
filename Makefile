CC = gcc
CFLAGS = -g -std=c11
EXECUTABLE = pa1
SRC_C = input.c


default: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_C)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(CFLAGS)


run:
	./$(EXECUTABLE)