/*
 * Exercise 03: NULL Check — SOLUTION
 *
 * Concept: EVERY heap allocation must be NULL-checked.
 *
 * Safe C Standard: int main(void), no scanf/atoi.
 * Use perror() for error reporting.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 12;

    /* First allocation */
    float *arr = malloc(count * sizeof(float));
    if (arr == NULL) {
        perror("malloc failed for arr");
        return EXIT_FAILURE;
    }

    /* Fill first array */
    for (size_t i = 0; i < count; i++) {
        arr[i] = (float)i * 0.5f;
    }

    printf("First array (%zu floats):\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("  arr[%zu] = %.1f\n", i, arr[i]);
    }

    /* Second allocation */
    size_t count2 = 6;
    float *more = malloc(count2 * sizeof(float));
    if (more == NULL) {
        perror("malloc failed for more");
        free(arr);
        return EXIT_FAILURE;
    }

    /* Fill second array */
    for (size_t i = 0; i < count2; i++) {
        more[i] = 100.0f - (float)i * 10.0f;
    }

    printf("\nSecond array (%zu floats):", count2);
    for (size_t i = 0; i < count2; i++) {
        printf(" %.1f", more[i]);
    }
    putchar('\n');

    /* Clean up both */
    free(arr);
    free(more);

    printf("All memory freed. Every allocation was checked.\n");
    return EXIT_SUCCESS;
}
