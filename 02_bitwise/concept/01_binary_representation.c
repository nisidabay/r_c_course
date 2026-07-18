/*
 * 01_binary_representation.c — What does an integer look like in binary?
 * Group 02 - Bitwise Operations
 *
 * An int in C is stored as a sequence of bits — 32 of them on most modern
 * systems.  The number 42, for example, is:
 *
 *   00000000 00000000 00000000 00101010
 *
 * This file shows how to inspect those bits one at a time using shifts
 * and a bitwise AND.
 *
 * The pattern: (n >> i) & 1  extracts the i-th bit (0-indexed from the
 * right, LSB = least significant bit).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * print_bits — print the binary representation of an unsigned int.
 *
 * Walks from bit 31 down to bit 0.  For each position, shift the
 * value right by i, then mask with 1 to isolate that single bit.
 */
static void print_bits(unsigned int n)
{
    /* Print a space every 8 bits for readability */
    for (int i = 31; i >= 0; i--) {
        putchar((n >> i) & 1 ? '1' : '0');
        if (i > 0 && i % 8 == 0)
            putchar(' ');
    }
    putchar('\n');
}

int main(void)
{
    printf("=== Binary Representation ===\n\n");

    /* Some examples */
    unsigned int vals[] = {0, 1, 7, 42, 255, 1024, 123456};
    int n = sizeof vals / sizeof vals[0];

    for (int i = 0; i < n; i++) {
        printf("%7u  decimal  =  ", vals[i]);
        print_bits(vals[i]);
    }

    printf("\n--- Try your own ---\n");
    printf("Enter an unsigned integer: ");

    char buf[64];
    if (fgets(buf, sizeof buf, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

    char *endptr;
    unsigned long val = strtoul(buf, &endptr, 10);
    if (endptr == buf || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%lu  decimal  =  ", val);
    print_bits((unsigned int)val);

    return EXIT_SUCCESS;
}

// Thinking in C:
// Bits are numbered from 0 (the least significant, rightmost) to 31
// (the most significant, leftmost) on a 32-bit system.
//
// (n >> i) & 1  does two things:
//   1. >> shifts all bits i positions to the right — the bit that was
//      at position i moves to position 0 (the LSB position).
//   2. & 1 masks everything except that single bit.
//
// This is the fundamental building block for ALL bitwise operations.
// Once you can inspect a bit, you can test it, set it, clear it, or
// toggle it — which is exactly what the next concepts will do.
