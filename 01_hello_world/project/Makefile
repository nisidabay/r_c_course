CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -Werror
LDFLAGS =

.PHONY: all clean run

all: sysinfo

sysinfo: project.c
	$(CC) $(CFLAGS) -o $@ $^

run: sysinfo
	./sysinfo

clean:
	$(RM) sysinfo
