/*
 * Exercise 01: Dynamically allocate and print a list of ints
 *
 * Modify this example so that the program:
 *   1. Checks if malloc returned NULL and exits with error
 *   2. Frees the allocated memory before returning
 *
 * Hint: add a NULL check after malloc and a free() call at the end.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const size_t count = 10;
    int *arr = (int *)malloc(count * sizeof(int));

    /* ---- ADD NULL CHECK HERE ---- */

    for (size_t i = 0; i < count; i++) {
        arr[i] = (int)(i * i);
    }

    printf("Squares: ");
    for (size_t i = 0; i < count; i++) {
        printf("%d%c", arr[i], i + 1 < count ? ' ' : '\n');
    }

    /* ---- ADD FREE HERE ---- */

    return EXIT_SUCCESS;
}
