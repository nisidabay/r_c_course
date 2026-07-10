/*
 * Exercise 01: Basic printf + return values
 *
 * Modify this example so that:
 *   1. Print three integers on three separate lines:
 *        10, 20, and 30.
 *   2. Return EXIT_FAILURE instead of EXIT_SUCCESS.
 *
 * Hint: you only need to change two things below.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Line 1: %d\n", 1);
    printf("Line 2: %d\n", 2);
    printf("Line 3: %d\n", 3);

    return EXIT_SUCCESS;
}
