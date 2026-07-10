CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -Werror
LDFLAGS =

.PHONY: all clean run

all: todo

todo: main.c
	$(CC) $(CFLAGS) -o $@ $^

run: todo
	./todo list

clean:
	$(RM) todo
