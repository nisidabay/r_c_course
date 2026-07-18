/*
 * 03_null_check.c
 * Group 07 — Dynamic Memory
 * Concept: EVERY heap allocation must be NULL-checked
 *
 * malloc (and calloc, realloc) can return NULL when the system
 * cannot satisfy the request — out of memory, address space
 * exhaustion, or a corrupted allocator.  Using a NULL pointer
 * is undefined behaviour (usually a segfault).  We check with
 * if (!ptr) and report the error with perror().
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
    size_t count = 10;
    int *scores = NULL;

    /* Attempt allocation */
    scores = malloc(count * sizeof(int));
    if (scores == NULL) {
        perror("malloc failed for scores");
        return EXIT_FAILURE;
    }

    /* Fill and print */
    for (size_t i = 0; i < count; i++) {
        scores[i] = (int)(i * 10);
    }

    printf("Allocated %zu scores successfully.\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("  scores[%zu] = %d\n", i, scores[i]);
    }

    /* A second allocation to drive the point home */
    int *more = malloc(5 * sizeof(int));
    if (more == NULL) {
        perror("malloc failed for more");
        free(scores);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < 5; i++) {
        more[i] = 100 - (int)i * 5;
    }

    printf("\nSecond allocation (%p):", (void*)more);
    for (size_t i = 0; i < 5; i++) {
        printf(" %d", more[i]);
    }
    putchar('\n');

    /* Clean up both allocations */
    free(scores);
    free(more);

    printf("\nAll memory freed.  Every allocation was checked.\n");
    return EXIT_SUCCESS;
}
/*
 * Thinking in C:
 * NULL-checking is not optional — it is defence against a real failure mode.
 * perror() prints the error message plus strerror(errno) for context.
 * If the first malloc fails, return immediately; there is nothing to free.
 * If later allocations fail, free everything already allocated before exit.
 */
