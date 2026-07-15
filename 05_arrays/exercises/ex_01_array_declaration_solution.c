/*
 * ex_01_array_declaration.c — SOLUTION
 * Group 05 — Arrays
 * Exercise 01: array declaration and initialization
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* 1. & 2. Declare an array with 6 elements, initialize with brace-enclosed list */
    int numbers[6] = { 10, 20, 30, 40, 50, 60 };

    /* 3. Partial initialization — declare 'partial' with 5 elements, set only first 3 */
    int partial[5] = { 100, 200, 300 };

    /* 4. Designated initializer — declare 'flags' with 8 elements.
     *    Set index 0 to 1, index 4 to 1, index 7 to 1. */
    int flags[8] = { [0] = 1, [4] = 1, [7] = 1 };

    /* Print results */
    printf("numbers[0] = %d (expected: 10)\n", numbers[0]);
    printf("numbers[5] = %d (expected: 60)\n", numbers[5]);
    printf("partial[3] = %d (expected: 0, zero-filled)\n", partial[3]);
    printf("flags[4]   = %d (expected: 1)\n", flags[4]);
    printf("flags[1]   = %d (expected: 0)\n", flags[1]);

    return EXIT_SUCCESS;
}
