/*
 * Exercise 04: calloc and realloc
 *
 * Concept: calloc for zero-initialised memory, realloc for resizing.
 * CRITICAL: Always use a TEMP pointer for realloc — never
 * ptr = realloc(ptr, n), because realloc can return NULL and
 * you would lose the original pointer.
 *
 * Fill in the blanks (marked /*@*//*@*/) to complete the program.
 * The program should:
 *   1. Allocate 4 ints with calloc (all zero-initialised)
 *   2. Fill them with values: 10, 20, 30, 40
 *   3. Grow the array to 7 elements using realloc with a temp pointer
 *   4. Fill the new slots with 50, 60, 70
 *   5. Print all elements
 *   6. Free
 *
 * Safe C Standard: int main(void), no scanf/atoi.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 4;

    /* calloc — zero-initialised allocation */
    int *data = /*@*/ calloc(count, sizeof(int)) /*@*/;
    if (data == NULL) {
        perror("calloc failed");
        return 1;
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
    int *temp = /*@*/ realloc(data, new_count * sizeof(int)) /*@*/;
    if (/*@*/temp == NULL/*@*/) {
        perror("realloc failed");
        free(data);
        return 1;
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

    /*@*/ free(data) /*@*/;
    return 0;
}
/*
 * Thinking in C:
 * calloc(N, sz) = malloc(N * sz) + memset(0).
 * realloc(NULL, n) acts like malloc(n); realloc(ptr, 0) acts like free(ptr).
 * Never write ptr = realloc(ptr, n) — if it returns NULL, you leak original.
 * Always use a temporary pointer, check it, then assign.
 */
