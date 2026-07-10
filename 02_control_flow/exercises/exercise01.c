/*
 * Exercise 01: Number classifier with if/else
 *
 * Modify this example so that the program correctly classifies
 * a number as POSITIVE, NEGATIVE, or ZERO.
 *
 * Hint: add if/else conditions inside the loop body. The
 * structure is there -- you just need to fill in the logic.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const int numbers[] = {5, -3, 0, 42, -128, 7, 0, -1};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);

    for (size_t i = 0; i < count; i++) {
        const int n = numbers[i];

        /* ---- YOUR CODE HERE ---- */
        /* Classify n as POSITIVE, NEGATIVE, or ZERO */

        (void)n; /* remove this line once you add your logic */

        printf("Number %d: \n", n);
    }

    return EXIT_SUCCESS;
}
