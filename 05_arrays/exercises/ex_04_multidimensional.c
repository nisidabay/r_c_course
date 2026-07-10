/*
 * ex_04_multidimensional.c
 * Group 05 — Arrays
 * Exercise 04: multi-dimensional arrays
 *
 * Fill in the blanks (marked with /* @FILL_ME */) to complete the program.
 * Work with a 2D integer matrix using nested loops.
 */

#include <stdio.h>

#define ROWS 3
#define COLS 4

int main(void) {
    /* A 3x4 matrix */
    int matrix[ROWS][COLS] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    };

    int r, c;

    /* 1. Print the matrix in row-major order (rows x columns) */
    printf("Matrix:\n");
    for (r = 0; r < /* @FILL_ME */; ++r) {
        for (c = 0; c < /* @FILL_ME */; ++c) {
            printf("%3d ", matrix[/* @FILL_ME */][/* @FILL_ME */]);
        }
        putchar('\n');
    }

    /* 2. Compute the sum of all elements */
    int total = 0;
    for (r = 0; r < ROWS; ++r) {
        for (c = 0; c < COLS; ++c) {
            total /* @FILL_ME */ matrix[r][c];
        }
    }
    printf("Total sum = %d (expected: 78)\n", total);

    /* 3. Compute the sum of each individual row */
    for (r = 0; r < ROWS; ++r) {
        int row_sum = 0;
        for (c = 0; c < COLS; ++c) {
            row_sum += matrix[r][c];
        }
        printf("Row %d sum = %d", r, row_sum);
        /* Row 0: 1+2+3+4=10, Row 1: 5+6+7+8=26, Row 2: 9+10+11+12=42 */
        putchar('\n');
    }

    return 0;
}

/*
 * After filling the blanks:
 *   Matrix should print as a 3x4 grid
 *   Total sum of all values = 78
 *   Row sums: 10, 26, 42
 */
