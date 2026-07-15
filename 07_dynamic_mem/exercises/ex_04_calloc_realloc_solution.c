/*
 * Exercise 04: calloc and realloc — SOLUTION
 *
 * Concept: calloc for zero-initialised memory, realloc for resizing.
 * CRITICAL: Always use a TEMP pointer for realloc.
 *
 * Safe C Standard: int main(void), no scanf/atoi.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 4;

    /* calloc — zero-initialised allocation */
    int *data = calloc(count, sizeof(int));
    if (data == NULL) {
        perror("calloc failed");
        return EXIT_FAILURE;
    }

    printf("After calloc (all zeroed):");
    for (size_t i = 0; i < count; i++) {
        printf(" %d", data[i]);
    }
    putchar('\n');

    /* Fill with values */
    for (size_t i = 0; i < count; i++) {
        data[i] = (int)((i + 1) * 10);
    }

    printf("After filling:");
    for (size_t i = 0; i < count; i++) {
        printf(" %d", data[i]);
    }
    putchar('\n');

    /* realloc — grow the array (TEMP POINTER pattern!) */
    size_t new_count = 7;
    int *temp = realloc(data, new_count * sizeof(int));
    if (temp == NULL) {
        perror("realloc failed");
        free(data);
        return EXIT_FAILURE;
    }
    data = temp;
    temp = NULL;

    /* Fill the new slots */
    for (size_t i = count; i < new_count; i++) {
        data[i] = (int)((i + 1) * 10);
    }

    printf("After realloc to %zu:", new_count);
    for (size_t i = 0; i < new_count; i++) {
        printf(" %d", data[i]);
    }
    putchar('\n');

    printf("\ncalloc gave us clean zeroes automatically.\n");
    printf("realloc preserved the first %zu elements.\n", count);
    printf("The TEMP pointer pattern kept data safe on failure.\n");

    free(data);
    return EXIT_SUCCESS;
}
