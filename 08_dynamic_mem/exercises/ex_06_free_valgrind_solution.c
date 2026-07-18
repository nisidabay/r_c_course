/*
 * Exercise 06: free / Valgrind — SOLUTION
 *
 * Concept: Free discipline — every malloc must be freed.
 * free(NULL) is safe. Double-free is UB. NULL after free.
 *
 * Safe C Standard: int main(void), no scanf/atoi.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *a = malloc(4 * sizeof(int));
    int *b = malloc(4 * sizeof(int));
    int *c = malloc(4 * sizeof(int));

    /* Check all allocations */
    if (a == NULL || b == NULL || c == NULL) {
        perror("malloc failed");
        free(a);
        free(b);
        free(c);
        return EXIT_FAILURE;
    }

    /* Fill arrays */
    for (size_t i = 0; i < 4; i++) {
        a[i] = (int)(i * 10);
        b[i] = (int)(i * 10 + 1);
        c[i] = (int)(i * 10 + 2);
    }

    printf("Before free: a[2]=%d  b[2]=%d  c[2]=%d\n", a[2], b[2], c[2]);

    /* Free everything */
    free(a);
    a = NULL;

    free(b);
    b = NULL;

    free(c);
    c = NULL;

    /*
     * Double-free example (safe because we NULL after free):
     * free(a);  // a is NULL — free(NULL) is safe
     *
     * Without NULL assignment:
     * free(a);  // first free — valid
     * free(a);  // second free — UNDEFINED BEHAVIOUR
     */

    printf("\nAll three arrays freed cleanly.\n");
    printf("All pointers NULLed after free.\n");
    printf("Check with: valgrind --leak-check=full ./ex_06_free_valgrind\n");

    return EXIT_SUCCESS;
}
