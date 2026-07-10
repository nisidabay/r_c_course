/*
 * ex_01_array_declaration.c
 * Group 05 — Arrays
 * Exercise 01: array declaration and initialization
 *
 * Fill in the blanks (marked with /* @FILL_ME */) to complete the program.
 * Read the comments to understand what each line should do.
 */

#include <stdio.h>

int main(void) {
    /* 1. Declare an integer array named 'numbers' with 6 elements */
    int numbers /* @FILL_ME */;

    /* 2. Initialize all 6 elements with a brace-enclosed list: 10, 20, 30, 40, 50, 60 */
    /* @FILL_ME */ = { 10, 20, 30, 40, 50, 60 };

    /* 3. Partial initialization — declare 'partial' with 5 elements, set only first 3 */
    int partial[5] = { 100, 200, 300 /* @FILL_ME */ };

    /* 4. Designated initializer — declare 'flags' with 8 elements.
     *    Set index 0 to 1, index 4 to 1, index 7 to 1. */
    int flags[8] = { /* @FILL_ME */ };

    /* Print results */
    printf("numbers[0] = %d (expected: 10)\n", numbers[0]);
    printf("numbers[5] = %d (expected: 60)\n", numbers[5]);
    printf("partial[3] = %d (expected: 0, zero-filled)\n", partial[3]);
    printf("flags[4]   = %d (expected: 1)\n", flags[4]);
    printf("flags[1]   = %d (expected: 0)\n", flags[1]);

    return 0;
}

/*
 * After filling the blanks:
 *   numbers[0] should be 10
 *   partial[3] should be 0 (zero-filled)
 *   flags[4] should be 1 (designated init)
 */
