/*
 * 04_calloc_realloc.c
 * Group 07 — Dynamic Memory
 * Concept: calloc for zero-initialised memory, realloc for resizing
 *
 * calloc(n, sz) allocates n * sz bytes AND zeroes every byte.
 * realloc(ptr, new_sz) resizes an existing allocation, preserving
 * content up to the minimum of old/new size.  CRITICAL: always use
 * a TEMP pointer for realloc — never ptr = realloc(ptr, n) directly,
 * because realloc can return NULL and you would lose the original ptr.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* --- calloc: zero-initialised allocation --- */
    size_t count = 5;
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
        data[i] = (int)(i * 10);
    }

    printf("After filling:");
    for (size_t i = 0; i < count; i++) {
        printf(" %d", data[i]);
    }
    putchar('\n');

    /* --- realloc: grow the array (TEMP POINTER pattern) --- */
    size_t new_count = 8;
    int *temp = realloc(data, new_count * sizeof(int));
    if (temp == NULL) {
        perror("realloc failed to grow");
        free(data);
        return EXIT_FAILURE;
    }
    data = temp;          /* only assign after success */
    temp = NULL;

    /* Fill the new slots */
    for (size_t i = count; i < new_count; i++) {
        data[i] = (int)(i * 10);
    }

    printf("After realloc to %zu:", new_count);
    for (size_t i = 0; i < new_count; i++) {
        printf(" %d", data[i]);
    }
    putchar('\n');

    printf("\nNote: calloc gave us clean zeroes automatically.\n");
    printf("      realloc preserved the first %zu elements.\n", count);
    printf("      realloc used a TEMP pointer — safe against NULL return.\n");

    free(data);
    return EXIT_SUCCESS;
}
/*
 * Thinking in C:
 * calloc = malloc + memset(0) — handy for arrays that start empty.
 * realloc(NULL, n) acts like malloc(n); realloc(ptr, 0) acts like free(ptr).
 * Never write  ptr = realloc(ptr, n)  — if it fails, you leak the original
 * allocation.  Always use a temporary pointer, check it, then assign.
 */
