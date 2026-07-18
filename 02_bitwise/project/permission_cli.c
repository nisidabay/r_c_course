/*
 * permission_cli.c — Permission Mask Builder
 * Group 02 - Bitwise Operations (Project)
 *
 * A CLI tool that reads permission flags like "read write execute"
 * and builds the corresponding Unix-style permission mask.
 *
 * Unix permissions use a 3-bit mask per category:
 *   r-- = 4  (read)
 *   -w- = 2  (write)
 *   --x = 1  (execute)
 *   rwx = 7  (read + write + execute)
 *
 * The program reads tokens from stdin, builds the mask using
 * bitwise OR, and displays the result in octal, decimal, and
 * symbolic (rwx) format.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic permission_cli.c -o permission_cli
 * Run:    ./permission_cli
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Permission flag constants */
#define PERM_READ    4
#define PERM_WRITE   2
#define PERM_EXECUTE 1

static void print_bits(unsigned int n)
{
    for (int i = 7; i >= 0; i--) {
        putchar((n >> i) & 1 ? '1' : '0');
        if (i > 0 && i % 4 == 0)
            putchar(' ');
    }
}

static void print_symbolic(unsigned int n)
{
    putchar((n & PERM_READ)    ? 'r' : '-');
    putchar((n & PERM_WRITE)   ? 'w' : '-');
    putchar((n & PERM_EXECUTE) ? 'x' : '-');
}

int main(void)
{
    char line[128];

    printf("=== Permission Mask Builder ===\n");
    printf("Enter permission names (read, write, execute) separated by\n");
    printf("spaces, or 'q' to quit.\n\n");

    while (1) {
        printf("permissions: ");
        if (fgets(line, sizeof line, stdin) == NULL)
            break;

        size_t len = strlen(line);
        if (len > 0 && line[len - 1] != '\n') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        } else if (len > 0) {
            line[len - 1] = '\0';
        }

        if (line[0] == 'q' && line[1] == '\0')
            break;

        /* Tokenise the line into words using strtok */
        unsigned int mask = 0;
        char *token = strtok(line, " \t");

        while (token) {
            if (strcmp(token, "read") == 0)
                mask |= PERM_READ;
            else if (strcmp(token, "write") == 0)
                mask |= PERM_WRITE;
            else if (strcmp(token, "execute") == 0)
                mask |= PERM_EXECUTE;
            else
                printf("  Unknown permission: '%s'\n", token);
            token = strtok(NULL, " \t");
        }

        printf("  Binary : ");
        print_bits(mask);
        printf("\n");
        printf("  Octal  : 0%o\n", mask);
        printf("  Decimal: %u\n", mask);
        printf("  Symbolic: ");
        print_symbolic(mask);
        printf("\n\n");
    }

    printf("Goodbye!\n");
    return EXIT_SUCCESS;
}

// Thinking in C:
// This project combines everything from this group into one
// practical tool.  Bitwise OR (|) combines flags, bitwise AND (&)
// tests them, and the whole thing mirrors how real operating
// systems manage file permissions.
//
// The same pattern appears throughout systems programming:
//   - open() uses O_RDONLY | O_CREAT | O_TRUNC
//   - mmap() uses PROT_READ | PROT_WRITE
//   - signal handlers use SA_RESTART | SA_NOCLDSTOP
//
// Bitwise flags are C's way of packing multiple booleans into
// a single integer — efficient, idiomatic, and everywhere.
