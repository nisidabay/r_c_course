/*
 * 05_bitwise_xor.c — The bitwise XOR operator: ^
 * Group 02 - Bitwise Operations
 *
 * x ^ y  (exclusive OR) produces a 1 bit where the operands DIFFER.
 *
 * Truth table for a single bit:
 *   0 ^ 0 = 0    0 ^ 1 = 1
 *   1 ^ 0 = 1    1 ^ 1 = 0
 *
 * Key properties:
 *   x ^ 0 = x       (anything XOR zero stays the same)
 *   x ^ x = 0       (anything XOR itself becomes zero)
 *   x ^ y ^ y = x   (XOR is its own inverse — two applications cancel)
 *
 * The last property is the foundation of the XOR swap trick and
 * simple encryption schemes.
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
    printf("=== Bitwise XOR (^) ===\n\n");

    unsigned int a = 0xCC;
    unsigned int b = 0xAA;

    printf("  a      =  ");
    print_bits(a);
    printf("  b      =  ");
    print_bits(b);
    printf("  a ^ b  =  ");
    print_bits(a ^ b);

    printf("\n--- XOR properties ---\n\n");

    unsigned int x = 0xAB;

    printf("  x      =  0x%X\n", x);
    printf("  x ^ 0  =  0x%X   (x ^ 0 = x)\n", x ^ 0);
    printf("  x ^ x  =  0x%X   (x ^ x = 0)\n", x ^ x);

    printf("\n--- Toggling bits ---\n");
    printf("  XOR with a mask toggles every bit the mask covers:\n");

    unsigned int val = 0xF0;
    unsigned int toggle = 0x3C;
    printf("  val          =  ");
    print_bits(val);
    printf("  toggle mask  =  ");
    print_bits(toggle);
    printf("  val ^ toggle =  ");
    print_bits(val ^ toggle);
    printf("  again        =  ");
    print_bits(val ^ toggle ^ toggle);   /* back to original */

    printf("\n  XOR twice restores the original — this is how simple\n");
    printf("  XOR-based ciphers work.\n");

    return EXIT_SUCCESS;
}

// Thinking in C:
// XOR is the most interesting bitwise operator because it's
// reversible.  Every bit flip is undone by a second flip with
// the same mask.
//
// This makes XOR useful for:
//   - Graphics: drawing a cursor over a background without
//     knowing the background (XOR twice = restore).
//   - Cryptography: one-time pads and stream ciphers.
//   - Assembly: the classic XOR swap (no temporary variable):
//        x ^= y;  y ^= x;  x ^= y;
//     (Try it!  But only on integers, not pointers.)
