CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -Werror
LDFLAGS =

.PHONY: all clean run

all: wc-lite

wc-lite: project.c
	$(CC) $(CFLAGS) -o $@ $^

run: wc-lite
	./wc-lite project.c

clean:
	$(RM) wc-lite
