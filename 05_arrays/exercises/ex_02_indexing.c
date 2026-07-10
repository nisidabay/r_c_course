/*
 * ex_02_indexing.c
 * Group 05 — Arrays
 * Exercise 02: array indexing and element access
 *
 * Fill in the blanks (marked with /* @FILL_ME */) to complete the program.
 * Use the subscript operator [] to read and write array elements.
 */

#include <stdio.h>

int main(void) {
    int data[7] = { 5, 15, 25, 35, 45, 55, 65 };

    /* 1. Print the first, third, and last elements using proper indices */
    printf("First: %d (expected: 5)\n", data[ /* @FILL_ME */ ]);
    printf("Third: %d (expected: 25)\n", data[ /* @FILL_ME */ ]);
    printf("Last:  %d (expected: 65)\n", data[ /* @FILL_ME */ ]);

    /* 2. Update the element at index 2 to 99 */
    /* @FILL_ME */ = 99;
    printf("After update, data[2] = %d (expected: 99)\n", data[2]);

    /* 3. Swap the first and last elements using a temporary variable */
    int tmp = data[0];
    data[0] = data[ /* @FILL_ME */ ];
    data[6] = /* @FILL_ME */;
    printf("After swap, data[0] = %d (expected: 65)\n", data[0]);
    printf("After swap, data[6] = %d (expected: 5)\n", data[6]);

    return 0;
}

/*
 * After filling the blanks:
 *   First element data[0] is 5
 *   Last element data[6] is 65
 *   After swap: data[0] becomes 65, data[6] becomes 5
 */
