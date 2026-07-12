/*
 * ex_02_indexing.c — SOLUTION
 * Group 05 — Arrays
 * Exercise 02: array indexing and element access
 */

#include <stdio.h>

int main(void) {
    int data[7] = { 5, 15, 25, 35, 45, 55, 65 };

    /* 1. Print the first, third, and last elements using proper indices */
    printf("First: %d (expected: 5)\n", data[0]);
    printf("Third: %d (expected: 25)\n", data[2]);
    printf("Last:  %d (expected: 65)\n", data[6]);

    /* 2. Update the element at index 2 to 99 */
    data[2] = 99;
    printf("After update, data[2] = %d (expected: 99)\n", data[2]);

    /* 3. Swap the first and last elements using a temporary variable */
    int tmp = data[0];
    data[0] = data[6];
    data[6] = tmp;
    printf("After swap, data[0] = %d (expected: 65)\n", data[0]);
    printf("After swap, data[6] = %d (expected: 5)\n", data[6]);

    return 0;
}
