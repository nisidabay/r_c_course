/*
 * 06_shift_ops.c — Left shift (<<) and right shift (>>)
 * Group 02 - Bitwise Operations
 *
 * x << n  shifts all bits of x to the LEFT by n positions.
 *         New bits on the right are filled with 0.
 *         Equivalent to multiplying by 2^n (for unsigned types).
 *
 * x >> n  shifts all bits of x to the RIGHT by n positions.
 *         For unsigned types, new bits on the LEFT are filled with 0.
 *         Equivalent to integer division by 2^n.
 *
 * Shift operators are how we construct masks dynamically:
 *   1 << n  gives you a 1-bit at position n (0-indexed from LSB).
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
    printf("=== Left Shift (<<) and Right Shift (>>) ===\n\n");

    unsigned int x = 1;

    printf("--- Left shift: 1 << n  (powers of two) ---\n");
    for (int n = 0; n <= 10; n++) {
        unsigned int r = x << n;
        printf("  1 << %2d  =  %5u  =  ", n, r);
        print_bits(r);
    }

    printf("\n--- Right shift: 1024 >> n  (division by powers of two) ---\n");
    unsigned int v = 1024;
    for (int n = 0; n <= 10; n++) {
        unsigned int r = v >> n;
        printf("  %4u >> %2d  =  %5u  =  ", v, n, r);
        print_bits(r);
    }

    printf("\n--- Building masks dynamically ---\n");

    /* Mask for bits 3, 5, 7 */
    unsigned int mask = (1 << 3) | (1 << 5) | (1 << 7);
    printf("  mask for bits 3,5,7  =  ");
    print_bits(mask);
    printf("  value: %u\n", mask);

    /* Range mask: bits 4 through 8 */
    unsigned int range = ((1 << 9) - 1) - ((1 << 4) - 1);
    printf("  bits 4-8            =  ");
    print_bits(range);
    printf("  value: %u\n", range);

    return EXIT_SUCCESS;
}

// Thinking in C:
// Shifts are some of the fastest operations on a CPU — typically
// a single cycle.  Compilers routinely turn multiplication and
// division by powers of two into shift instructions automatically.
//
// CAUTION: shifting by an amount >= the width of the type (>= 32
// for unsigned int) is undefined behavior.  Always bound-check
// your shift amounts.
//
//   x << 32   ← UNDEFINED BEHAVIOR
//   x >> 100  ← UNDEFINED BEHAVIOR
//
// Also, right-shifting a signed negative integer is
// implementation-defined — prefer unsigned types for bitwise ops.
