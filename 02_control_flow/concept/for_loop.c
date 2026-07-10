/*
 * How do I repeat code with for loops?
 *
 * A for loop bundles initialisation, condition, and update
 * into one compact line:  for (init; condition; update)
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Count up */
    printf("Counting up:\n");
    for (int i = 0; i < 5; ++i) {
        printf("  i = %d\n", i);
    }

    /* Count down */
    printf("Counting down:\n");
    for (int i = 5; i > 0; --i) {
        printf("  i = %d\n", i);
    }

    /* Multiple initialisers and updates (comma operator) */
    printf("Sum from 1 to 10:\n");
    int sum = 0;
    for (int i = 1; i <= 10; ++i) {
        sum += i;
    }
    printf("  sum = %d\n", sum);

    /* Loop with multiple variables */
    for (int i = 0, j = 10; i < j; ++i, --j) {
        printf("  i=%d  j=%d\n", i, j);
    }

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * The for loop's three clauses are all optional.  A missing
 * condition is treated as always-true, creating an infinite
 * loop:  for (;;) { ... }.  Prefer ++i over i++ in loops --
 * the prefix form has no temporary copy, which matters with
 * C++ iterators but is a good habit to keep in C too.
 * ============================================================
 */


// 💡 Thinking in C:
// for(init; condition; increment) is the workhorse. Control every part explicitly.
