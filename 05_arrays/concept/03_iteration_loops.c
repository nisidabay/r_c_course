/*
 * 03_iteration_loops.c
 * Group 05 — Arrays
 * Concept: iterating over arrays with for loops
 *
 * A for loop with a counter variable is the idiomatic way to
 * walk through every element of an array.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int scores[8] = { 83, 91, 76, 88, 95, 72, 89, 84 };
    int i;

    /* Print every element */
    printf("All scores: ");
    for (i = 0; i < 8; ++i) {
        printf("%d ", scores[i]);
    }
    putchar('\n');

    /* Compute sum and average */
    int sum = 0;
    for (i = 0; i < 8; ++i) {
        sum += scores[i];
    }
    printf("Sum: %d   Average: %d\n", sum, sum / 8);

    /* Find the maximum */
    int max = scores[0];
    for (i = 1; i < 8; ++i) {
        if (scores[i] > max) {
            max = scores[i];
        }
    }
    printf("Maximum score: %d\n", max);

    /* Print only passing scores (>= 80) */
    printf("Passing scores: ");
    for (i = 0; i < 8; ++i) {
        if (scores[i] >= 80) {
            printf("%d ", scores[i]);
        }
    }
    putchar('\n');

    return EXIT_SUCCESS;
}
/*
 * Thinking in C:
 * The loop variable is the index; the loop body does the work.
 * Two invariants: start at 0, stop before N.
 * Breaking those invariants is the #1 source of off-by-one bugs.
 */