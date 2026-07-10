/*
 * Exercise 02: malloc — SOLUTION
 *
 * Concept: Allocating memory with malloc, using sizeof(T), and freeing.
 *
 * Safe C Standard: int main(void), no scanf/atoi. NULL-check malloc.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 8;

    /* Allocate space for 'count' doubles */
    double *values = malloc(count * sizeof(double));
    if (values == NULL) {
        printf("ERROR: malloc failed\n");
        return 1;
    }

    /* Fill with values */
    for (size_t i = 0; i < count; i++) {
        values[i] = (double)i * 1.5;
    }

    /* Print the values */
    printf("Allocated %zu doubles on the heap (sizeof(double) = %zu bytes):\n",
           count, sizeof(double));
    for (size_t i = 0; i < count; i++) {
        printf("  values[%zu] = %.1f\n", i, values[i]);
    }

    printf("\nTotal bytes allocated: %zu\n", count * sizeof(double));

    /* Free the memory */
    free(values);
    values = NULL;

    printf("Memory freed successfully.\n");
    return 0;
}
