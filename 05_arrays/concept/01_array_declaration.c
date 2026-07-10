/*
 * 01_array_declaration.c
 * Group 05 — Arrays
 * Concept: declaring and initializing arrays in C11
 *
 * Shows: type name[N], brace-enclosed initializer lists,
 *        designated initializers (C11), partial initialization.
 */

#include <stdio.h>

int main(void) {
    /* Full initialization — all 5 elements set explicitly */
    int scores[5] = { 85, 92, 78, 91, 88 };

    /* Partial initialization — remaining elements are zero-filled */
    int temperatures[7] = { 22, 24, 19 };

    /* Designated initializers (C11) — set specific indices out of order */
    int readings[6] = { [0] = 100, [3] = 75, [5] = 50 };

    printf("Scores:       %d %d %d %d %d\n",
           scores[0], scores[1], scores[2], scores[3], scores[4]);

    printf("Temperatures: %d %d %d %d %d %d %d\n",
           temperatures[0], temperatures[1], temperatures[2],
           temperatures[3], temperatures[4], temperatures[5],
           temperatures[6]);

    printf("Readings:     %d %d %d %d %d %d\n",
           readings[0], readings[1], readings[2],
           readings[3], readings[4], readings[5]);

    return 0;
}
/*
 * Thinking in C:
 * An array reserves N contiguous slots of the same type.
 * Partial init zero-fills the tail — a safety net for beginners.
 * Designated init lets you name which slot you mean; useful for
 * sparse tables or config-style arrays.
 */