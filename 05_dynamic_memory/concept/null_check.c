/*
 * How do I check for allocation failures?
 *
 * This file demonstrates checking every malloc and realloc call,
 * using perror on failure, and cleaning up partial allocations
 * on error.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* --- Check every malloc --- */
    int *a = (int *)malloc(100 * sizeof(int));
    if (a == NULL) {
        perror("malloc failed for array a");
        return EXIT_FAILURE;
    }

    int *b = (int *)malloc(200 * sizeof(int));
    if (b == NULL) {
        perror("malloc failed for array b");
        free(a);
        return EXIT_FAILURE;
    }

    /* --- Check every realloc --- */
    int *tmp = (int *)realloc(a, 400 * sizeof(int));
    if (tmp == NULL) {
        perror("realloc failed for array a");
        free(a);
        free(b);
        return EXIT_FAILURE;
    }
    a = tmp;

    /* Use the memory */
    for (size_t i = 0; i < 100; i++) {
        a[i] = (int)i;
    }
    for (size_t i = 0; i < 200; i++) {
        b[i] = (int)(i * 2);
    }

    printf("a[42] = %d, b[42] = %d\n", a[42], b[42]);

    /* Clean up */
    free(a);
    free(b);

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// Check for NULL after every allocation. Dereferencing NULL is a crash or worse — undefined behavior.
