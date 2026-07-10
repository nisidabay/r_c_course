/*
 * 02_indexing.c
 * Group 05 — Arrays
 * Concept: accessing elements with the subscript operator a[i]
 *
 * C does NOT check array bounds at runtime.  The programmer is
 * responsible for staying within [0, N-1].  Out-of-range access
 * reads or corrupts adjacent memory — undefined behaviour.
 */

#include <stdio.h>

int main(void) {
    int grades[5] = { 87, 92, 76, 94, 81 };

    /* Valid accesses — indices 0 through 4 */
    printf("First grade:  %d  (grades[0])\n", grades[0]);
    printf("Third grade:  %d  (grades[2])\n", grades[2]);
    printf("Last grade:   %d  (grades[4])\n", grades[4]);

    /* Writing through a valid index */
    grades[1] = 95;
    printf("After update: grades[1] = %d\n", grades[1]);

    /* The classic bounds pitfall — this compiles and runs silently */
    printf("Out of bounds (grades[5]): %d   (garbage / crash)\n", grades[5]);

    /* grades[-1] is also syntactically valid — and equally dangerous */
    printf("Negative index (grades[-1]): %d  (undefined behaviour)\n", grades[-1]);

    return 0;
}
/*
 * Thinking in C:
 * a[i] is *(a + i) — pure pointer arithmetic.  No guard rails.
 * Bounds checking costs runtime; C trusts you.
 * Discipline: always know your array length, and never exceed it.
 */