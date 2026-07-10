/*
 * 04_multidimensional.c
 * Group 05 — Arrays
 * Concept: 2D arrays and row-major memory layout
 *
 * int matrix[ROWS][COLS] is stored row by row in memory.
 * Nested loops are the natural way to traverse both dimensions.
 */

#include <stdio.h>

#define ROWS 3
#define COLS 4

int main(void) {
    /* A 3x4 grade matrix: rows are students, columns are assignments */
    int grades[ROWS][COLS] = {
        { 85, 90, 78, 92 },
        { 73, 88, 91, 80 },
        { 95, 87, 84, 89 }
    };

    int r, c;

    /* Print the entire matrix */
    printf("Grade matrix (%d students, %d assignments):\n\n", ROWS, COLS);
    for (r = 0; r < ROWS; ++r) {
        printf("Student %d: ", r + 1);
        for (c = 0; c < COLS; ++c) {
            printf("%3d ", grades[r][c]);
        }
        putchar('\n');
    }

    /* Compute each student's average */
    putchar('\n');
    for (r = 0; r < ROWS; ++r) {
        int row_sum = 0;
        for (c = 0; c < COLS; ++c) {
            row_sum += grades[r][c];
        }
        printf("Student %d average: %d\n", r + 1, row_sum / COLS);
    }

    /* Compute each assignment's average */
    putchar('\n');
    for (c = 0; c < COLS; ++c) {
        int col_sum = 0;
        for (r = 0; r < ROWS; ++r) {
            col_sum += grades[r][c];
        }
        printf("Assignment %d average: %d\n", c + 1, col_sum / ROWS);
    }

    return 0;
}
/*
 * Thinking in C:
 * Row-major means grades[1][0] sits right after grades[0][COLS-1].
 * The outer loop chooses the row; the inner loop walks the columns.
 * Swap the loops to traverse column-first — same data, different view.
 */