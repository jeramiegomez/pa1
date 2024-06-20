CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS =
SRCS = input.c  # List all your .c source files here
OBJS = $(SRCS:.c=.o)
TARGET = pa1

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
