/*
 * 03_bitwise_and.c — The bitwise AND operator: &
 * Group 02 - Bitwise Operations
 *
 * x & y  produces a 1 bit ONLY where BOTH operands have a 1.
 *
 * Truth table for a single bit:
 *   0 & 0 = 0    0 & 1 = 0
 *   1 & 0 = 0    1 & 1 = 1
 *
 * The most common use: masking — extracting specific bits.
 *   x & 0xF    keeps only the lowest 4 bits of x
 *   (x >> i) & 1  extracts the i-th bit (concept 01)
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
    printf("=== Bitwise AND (&) ===\n\n");

    unsigned int a = 0xCC;   /* 204 in decimal */
    unsigned int b = 0xAA;   /* 170 in decimal */

    printf("  a      =  ");
    print_bits(a);
    printf("  b      =  ");
    print_bits(b);
    printf("  a & b  =  ");
    print_bits(a & b);

    printf("\n--- Masking examples ---\n\n");

    /* Low nibble (lowest 4 bits) */
    unsigned int val = 0xAB;
    unsigned int low_nibble = val & 0x0F;
    printf("  val          =  0x%X  =  ", val);
    print_bits(val);
    printf("  val & 0x0F   =  0x%X  =  ", low_nibble);
    print_bits(low_nibble);

    /* Check if bit 3 is set */
    unsigned int mask = 1 << 3;     /* 0b1000 = 8 */
    unsigned int flags = 0xB4;
    printf("\n  flags        =  ");
    print_bits(flags);
    printf("  mask (1<<3)  =  ");
    print_bits(mask);
    printf("  flags & mask =  %s\n",
           (flags & mask) ? "NON-ZERO → bit 3 IS set" : "ZERO → bit 3 is NOT set");

    /* Check if a number is even or odd using LSB */
    printf("\n--- Quick check: even or odd ---\n");
    printf("  42 & 1 = %d  → 42 is %s\n", 42 & 1, (42 & 1) ? "odd" : "even");
    printf("  7  & 1 = %d  → 7  is %s\n", 7 & 1, (7 & 1) ? "odd" : "even");

    return EXIT_SUCCESS;
}

// Thinking in C:
// & is the bitwise version of && (logical AND).  The difference:
//   (a > 0) && (b > 0)  — logical AND, result is 0 or 1
//   a & b               — bitwise AND, result is an integer
//
// Common & idioms:
//   x & (x - 1)  — clears the lowest set bit (used in popcount)
//   x & 1        — checks if x is odd (LSB = 1)
//   x & -x       — isolates the lowest set bit
// Some of these will appear in the exercises!
