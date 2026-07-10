/*
 * How do I automate builds with Makefiles?
 *
 * This file demonstrates how Makefiles automate compilation.
 * A Makefile defines targets, dependencies, and recipes.
 *
 * Sample Makefile:
 *   CC = gcc
 *   CFLAGS = -std=c11 -Wall -Wextra -pedantic -Werror
 *   TARGET = build_info
 *
 *   all: $(TARGET)
 *
 *   $(TARGET): makefiles_intro.c
 *       $(CC) $(CFLAGS) -o $(TARGET) makefiles_intro.c
 *
 *   clean:
 *       rm -f $(TARGET)
 *
 *   .PHONY: all clean
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Build system: Make\n");
    printf("Compiler: gcc\n");
    printf("Language standard: C11\n");

    /* In a real Makefile build, these would come from -D flags.
     * Here we simulate what a well-configured build provides. */
    printf("CC        = gcc\n");
    printf("CFLAGS    = -std=c11 -Wall -Wextra -pedantic -Werror\n");
    printf("OUTPUT    = build_info\n");

    return EXIT_SUCCESS;
}

/* Thinking in C: Makefiles encode the build recipe so every compilation
 * is repeatable, documented, and automated. Define variables for
 * compiler, flags, and targets so a single 'make' rebuilds correctly. */


// 💡 Thinking in C:
// Makefiles define targets, dependencies, and commands. CC, CFLAGS, and LDFLAGS are the standard variables.
