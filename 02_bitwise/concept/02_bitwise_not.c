/*
 * 02_bitwise_not.c — The bitwise NOT operator: ~
 * Group 02 - Bitwise Operations
 *
 * ~x  flips every bit in x: 0 becomes 1, 1 becomes 0.
 *
 * On a 32-bit system:
 *   ~0   = 0xFFFFFFFF  (all 32 bits set to 1)
 *   ~42  = 0xFFFFFFD5  (all bits flipped)
 *
 * In two's complement, ~x is equivalent to -(x + 1).
 * That is a consequence of how signed integers work, not a
 * property of ~ itself — the operator simply flips bits.
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
    printf("=== Bitwise NOT (~) ===\n\n");

    unsigned int x = 42;
    printf("  x   = %10u  =  ", x);
    print_bits(x);

    unsigned int nx = ~x;
    printf("  ~x  = %10u  =  ", nx);
    print_bits(nx);

    printf("\n--- Edge cases ---\n");

    unsigned int zero = 0;
    printf("  ~0  = %10u  =  ", ~zero);
    print_bits(~zero);

    unsigned int all_ones = ~0U;
    printf("  ~0U = %10u  =  ", all_ones);
    print_bits(all_ones);
    printf("  ~0U as signed: %d\n", (int)all_ones);   /* prints -1 */

    printf("\nKey insight: ~x flips EVERY bit.  On a 32-bit system,\n");
    printf("~0 gives you 32 ones — which happens to be -1 in two's\n");
    printf("complement signed representation.\n");

    return EXIT_SUCCESS;
}

// Thinking in C:
// ~ is a unary operator — it applies to a single operand.
// It is NOT the same as logical NOT (!), which turns any non-zero
// value into 0, and 0 into 1.
//
//   !42  == 0       (logical NOT)
//   ~42  == 0xFFFFFFD5  (bitwise NOT — very different!)
//
// Distinguishing ~ and ! is one of the most common beginner mistakes
// in C.  Remember: ~ is for BITS, ! is for TRUTH.
