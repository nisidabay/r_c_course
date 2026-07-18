/*
 * ex_04_multidimensional.c — SOLUTION
 * Group 05 — Arrays
 * Exercise 04: multi-dimensional arrays
 */

#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 4

int main(void) {
    int matrix[ROWS][COLS] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    };

    int r, c;

    /* 1. Print the matrix in row-major order */
    printf("Matrix:\n");
    for (r = 0; r < ROWS; ++r) {
        for (c = 0; c < COLS; ++c) {
            printf("%3d ", matrix[r][c]);
        }
        putchar('\n');
    }

    /* 2. Compute the sum of all elements */
    int total = 0;
    for (r = 0; r < ROWS; ++r) {
        for (c = 0; c < COLS; ++c) {
            total += matrix[r][c];
        }
    }
    printf("Total sum = %d (expected: 78)\n", total);

    /* 3. Compute the sum of each row */
    for (r = 0; r < ROWS; ++r) {
        int row_sum = 0;
        for (c = 0; c < COLS; ++c) {
            row_sum += matrix[r][c];
        }
        printf("Row %d sum = %d\n", r, row_sum);
    }

    return EXIT_SUCCESS;
}
