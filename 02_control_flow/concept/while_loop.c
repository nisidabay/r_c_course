/*
 * How do I repeat code with while/do-while?
 *
 * while checks the condition before each iteration.
 * do-while checks after, guaranteeing at least one execution.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* while loop -- check first */
    int i = 0;
    printf("while loop:\n");
    while (i < 5) {
        printf("  i = %d\n", i);
        ++i;
    }

    /* do-while loop -- execute at least once */
    int j = 0;
    printf("do-while loop:\n");
    do {
        printf("  j = %d\n", j);
        ++j;
    } while (j < 5);

    /* Demonstrating do-while always runs once */
    int k = 100;
    printf("do-while with false condition:\n");
    do {
        printf("  This runs once even though k=%d >= 5.\n", k);
        ++k;
    } while (k < 5);

    /* Sentinel-controlled loop: stop when value is -1 */
    printf("Counting down with a sentinel:\n");
    int count = 5;
    while (count >= 0) {
        printf("  %d\n", count);
        --count;
    }

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * The while loop is the fundamental repetition construct in
 * C; for loops are syntactic sugar built on top of while.
 * Choose while when the number of iterations is not known
 * ahead of time.  Choose do-while when the loop body must
 * execute at least once regardless of the condition.
 * ============================================================
 */


// 💡 Thinking in C:
// while repeats as long as the condition is true. while(1) is infinite.
