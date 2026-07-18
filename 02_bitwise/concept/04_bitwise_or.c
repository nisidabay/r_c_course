/*
 * 04_bitwise_or.c — The bitwise OR operator: |
 * Group 02 - Bitwise Operations
 *
 * x | y  produces a 1 bit where EITHER operand has a 1.
 *
 * Truth table for a single bit:
 *   0 | 0 = 0    0 | 1 = 1
 *   1 | 0 = 1    1 | 1 = 1
 *
 * Most common use: setting (turning on) specific bits.
 *   x | mask   turns on every bit that is 1 in mask.
 *
 * This is how real programs combine flags:
 *   int mode = O_RDWR | O_CREAT;   // open() flags
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_bits(unsigned int n)
{
    for (int i = 31; i >= 0; i--) {
        putchar((n >> i) & 1 ? '1' : '0');
        if (i > 0 && i % 8 == 0)
            putchar(' ');
    }
    putchar('\n');
}

int main(void)
{
    printf("=== Bitwise OR (|) ===\n\n");

    unsigned int a = 0xCC;
    unsigned int b = 0xAA;

    printf("  a      =  ");
    print_bits(a);
    printf("  b      =  ");
    print_bits(b);
    printf("  a | b  =  ");
    print_bits(a | b);

    printf("\n--- Setting bits with OR ---\n\n");

    /* Start with some flags, turn on bit 2 and bit 5 */
    unsigned int flags = 0x10;
    unsigned int mask  = (1 << 2) | (1 << 5);   /* bits 2 and 5 */

    printf("  flags (initial)   =  ");
    print_bits(flags);
    printf("  mask (bits 2 & 5) =  ");
    print_bits(mask);
    printf("  flags | mask      =  ");
    print_bits(flags | mask);

    /* Combining multiple flags (like real APIs) */
    printf("\n--- Combining flags (like open() does) ---\n");

#define FLAG_READ  0x1
#define FLAG_WRITE 0x2
#define FLAG_EXEC  0x4

    unsigned int mode = FLAG_READ | FLAG_EXEC;   /* read + execute */
    printf("  mode = FLAG_READ | FLAG_EXEC  =  0b");
    print_bits(mode);
    printf("  Numeric value: %u\n", mode);

    return EXIT_SUCCESS;
}

// Thinking in C:
// | is the bitwise version of || (logical OR).  The difference:
//   (x == 0) || (y == 0)  — logical OR, result is 0 or 1
//   x | y                 — bitwise OR, result is an integer
//
// & clears bits, | sets bits.  Together they form the foundation
// of bit-field manipulation that you'll see in file permissions,
// system call flags, and device registers throughout systems
// programming.
