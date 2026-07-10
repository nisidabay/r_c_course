/*
 * Exercise 03: NULL Check
 *
 * Concept: EVERY heap allocation must be NULL-checked.
 *
 * Fill in the blanks (marked /*@*//*@*/) to complete the program.
 * The program should:
 *   1. Allocate an array of 12 floats
 *   2. NULL-check both allocations
 *   3. Fill with values: arr[i] = i * 0.5f
 *   4. Free both allocations
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
    if (/*@*/arr == NULL/*@*/) {
        perror("malloc failed for arr");
        return 1;
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
    float *more = /*@*/ malloc(count2 * sizeof(float)) /*@*/;
    if (more == NULL) {
        perror("malloc failed for more");
        /*@*/ free(arr) /*@*/;
        return 1;
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
    /*@*/ free(arr) /*@*/;
    /*@*/ free(more) /*@*/;

    printf("All memory freed. Every allocation was checked.\n");
    return 0;
}
/*
 * Thinking in C:
 * NULL-checking is defence against a real failure mode.
 * perror() prints the error message plus system error info.
 * If the first malloc fails, nothing to free — return directly.
 * If later allocations fail, free everything allocated so far.
 */
