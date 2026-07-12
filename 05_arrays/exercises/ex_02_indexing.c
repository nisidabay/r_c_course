/*
 * ex_02_indexing.c
 * Group 05 — Arrays
 * Exercise 02: array indexing and element access
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * Use the subscript operator [] to read and write array elements.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int data[7] = { 5, 15, 25, 35, 45, 55, 65 };

    /* 1. Print the first, third, and last elements using proper indices */
    printf("First: %d (expected: 5)\n", data[0]);  // FIX ME
    printf("Third: %d (expected: 25)\n", data[2]);  // FIX ME
    printf("Last:  %d (expected: 65)\n", data[6]);  // FIX ME

    /* 2. Update the element at index 2 to 99 */
    data[2] = 99;  // FIX ME
    printf("After update, data[2] = %d (expected: 99)\n", data[2]);

    /* 3. Swap the first and last elements using a temporary variable */
    int tmp = data[0];
    data[0] = data[6];  // FIX ME
    data[6] = tmp;  // FIX ME
    printf("After swap, data[0] = %d (expected: 65)\n", data[0]);
    printf("After swap, data[6] = %d (expected: 5)\n", data[6]);

    return EXIT_SUCCESS;
}

/*
 * After filling the blanks:
 *   First element data[0] is 5
 *   Last element data[6] is 65
 *   After swap: data[0] becomes 65, data[6] becomes 5
 */
