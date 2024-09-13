CC = gcc
CFLAGS = -Wall -Wextra

all: part1 part2

part1: part1.c
	$(CC) $(CFLAGS) -o $@ $^

part2: part2.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGRAM)

.PHONY: all clean