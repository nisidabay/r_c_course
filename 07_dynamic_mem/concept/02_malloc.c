/*
 * 02_malloc.c
 * Group 07 — Dynamic Memory
 * Concept: malloc, sizeof(T), freeing, and checking success
 *
 * malloc(n) allocates n bytes from the heap and returns a pointer
 * to the first byte (void*).  We use sizeof(T) * count to compute
 * the right number of bytes.  Every malloc MUST be checked — it
 * returns NULL on failure — and eventually freed.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 6;
    int *data = NULL;

    /* Allocate space for 'count' integers */
    data = malloc(count * sizeof(int));
    if (data == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    /* Fill the allocated array */
    for (size_t i = 0; i < count; i++) {
        data[i] = (int)(i * 10 + 5);
    }

    /* Print what we stored */
    printf("Allocated %zu ints on the heap (sizeof(int) = %zu bytes):\n",
           count, sizeof(int));
    for (size_t i = 0; i < count; i++) {
        printf("  data[%zu] = %d\n", i, data[i]);
    }

    printf("\nTotal heap bytes allocated: %zu\n", count * sizeof(int));
    printf("Pointer value: %p\n", (void*)data);

    /* Free the memory so it can be reused */
    free(data);
    data = NULL;   /* optional: prevents dangling pointer reuse */

    printf("\nMemory freed successfully.\n");
    return EXIT_SUCCESS;
}
/*
 * Thinking in C:
 * malloc returns void*, implicitly convertible to any pointer type.
 * Always write malloc(N * sizeof(T)) — never hand-calculate byte counts.
 * Every malloc pairs with a free; forgetting causes a leak.
 * Check for NULL before using the pointer — malloc can and does fail.
 */
