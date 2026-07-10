/*
 * ex_03_iteration.c
 * Group 05 — Arrays
 * Exercise 03: iterating over arrays with for loops
 *
 * Fill in the blanks (marked with /* @FILL_ME */) to complete the program.
 * Use for loops to traverse arrays, compute sums, and find values.
 */

#include <stdio.h>

int main(void) {
    int values[10] = { 3, 7, 2, 9, 4, 8, 1, 6, 5, 0 };
    int i;

    /* 1. Compute the sum of all elements using a for loop */
    int sum = 0;
    for (i = 0; i < /* @FILL_ME */; ++i) {
        sum /* @FILL_ME */ values[i];
    }
    printf("Sum = %d (expected: 45)\n", sum);

    /* 2. Count how many values are greater than 5 */
    int count = 0;
    for (i = 0; i < 10; ++i) {
        if (values[i] /* @FILL_ME */ 5) {
            /* @FILL_ME */;
        }
    }
    printf("Count > 5 = %d (expected: 4)\n", count);

    /* 3. Find and print only the even values */
    printf("Even values: ");
    for (i = 0; i < 10; ++i) {
        if (values[i] /* @FILL_ME */ 2 == 0) {
            printf("%d ", values[i]);
        }
    }
    printf("(expected: 2 4 8 6 0)\n");

    return 0;
}

/*
 * After filling the blanks:
 *   Sum of 3+7+2+9+4+8+1+6+5+0 = 45
 *   Values > 5: 7, 9, 8, 6  → count = 4
 *   Even values: 2, 4, 8, 6, 0
 */
