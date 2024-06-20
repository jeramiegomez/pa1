CC = gcc
CFLAGS = -g -std=c11
EXECUTABLE = pa1
SRC_C = test.c


default: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_C)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(CFLAGS)


run:
	./$(EXECUTABLE)