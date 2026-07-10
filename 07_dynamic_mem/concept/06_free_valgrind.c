/*
 * 06_free_valgrind.c
 * Group 07 — Dynamic Memory
 * Concept: free discipline, double-free UB, and valgrind
 *
 * Every malloc/calloc/realloc must eventually be freed.
 * free(NULL) is safe — freeing the same pointer twice
 * is undefined behaviour.  Setting a pointer to NULL after
 * freeing makes the subsequent free safe.  valgrind is the
 * standard tool to detect leaks, use-after-free, and double-free.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *a = malloc(3 * sizeof(int));
    int *b = malloc(3 * sizeof(int));

    if (a == NULL || b == NULL) {
        perror("initial malloc failed");
        free(a);    /* safe even if a is NULL */
        free(b);
        return 1;
    }

    a[0] = 10; a[1] = 20; a[2] = 30;
    b[0] = 40; b[1] = 50; b[2] = 60;

    printf("Before free: a[1]=%d  b[1]=%d\n", a[1], b[1]);

    /* Free in the correct order */
    free(a);
    a = NULL;       /* now safe — subsequent free(a) is harmless */

    /*
     * If we forgot b entirely, valgrind would report:
     *   3 bytes in 1 blocks are definitely lost
     * Run: valgrind --leak-check=full ./06_free_valgrind
     */

    free(b);
    b = NULL;

    /*
     * double-free example (commented out because it is UB):
     *
     *   free(a);   // a is already freed AND set to NULL
     *              // free(NULL) is safe, so this would be OK.
     *
     * But without NULL assignment:
     *   free(a);   // first free — valid
     *   free(a);   // second free — UNDEFINED BEHAVIOUR (crash/corruption)
     */

    printf("\nBoth allocations freed cleanly.\n");
    printf("Check with: valgrind --leak-check=full ./06_free_valgrind\n");

    return 0;
}
/*
 * Thinking in C:
 * free(NULL) is safe and defined — exploit this by NULLing freed pointers.
 * Undefined behaviour from double-free may not crash immediately, but
 * it corrupts the allocator's internal bookkeeping.  Catch it early
 * with valgrind (or AddressSanitizer: gcc -fsanitize=address).
 * Every allocation is a liability — minimise lifetime, free promptly.
 */
