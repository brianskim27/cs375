CC = gcc
CFLAGS = -Wall -Wextra

PROGRAM = submission

all: $(PROGRAM)

$(PROGRAM): submission.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f $(PROGRAM)

.PHONY: all clean