/*
 * Exercise 02: malloc
 *
 * Concept: Allocating memory with malloc, using sizeof(T), and freeing.
 *
 * Fill in the blanks (marked /*@*//*@*/) to complete the program.
 * The program should:
 *   1. Allocate an array of 8 doubles on the heap
 *   2. Fill it with values: value[i] = i * 1.5
 *   3. Print all values
 *   4. Free the memory
 *
 * Safe C Standard: int main(void), no scanf/atoi. NULL-check malloc.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 8;

    /* Allocate space for 'count' doubles */
    double *values = /*@*/ malloc(count * sizeof(double)) /*@*/;
    if (values == NULL) {
        printf("ERROR: malloc failed\n");
        return 1;
    }

    /* Fill with values */
    for (size_t i = 0; i < count; i++) {
        /*@*/ values[i] /*@*/ = (double)i * 1.5;
    }

    /* Print the values */
    printf("Allocated %zu doubles on the heap (sizeof(double) = %zu bytes):\n",
           count, sizeof(double));
    for (size_t i = 0; i < count; i++) {
        printf("  values[%zu] = %.1f\n", i, /*@*/ values[i] /*@*/);
    }

    printf("\nTotal bytes allocated: %zu\n", count * sizeof(double));

    /* Free the memory */
    /*@*/ free(values) /*@*/;
    values = NULL;

    printf("Memory freed successfully.\n");
    return 0;
}
/*
 * Thinking in C:
 * malloc(N * sizeof(T)) allocates N elements of type T.
 * sizeof(T) ensures portability — never hardcode byte counts.
 * Always check for NULL before using the pointer.
 * Every malloc must be paired with a free.
 */
