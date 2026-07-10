CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -Werror
LDFLAGS =

.PHONY: all clean run

all: uniq

uniq: project.c
	$(CC) $(CFLAGS) -o $@ $^

run: uniq
	echo -e "a\na\nb" | ./uniq

clean:
	$(RM) uniq
