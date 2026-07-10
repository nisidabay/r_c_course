/*
 * How do I make decisions with if/else?
 *
 * if, else if, else, and nested conditions let your program
 * branch based on boolean expressions.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const int temperature = 75;

    if (temperature > 90) {
        printf("It's hot outside.\n");
    } else if (temperature > 60) {
        printf("It's warm outside.\n");
    } else if (temperature > 32) {
        printf("It's cool outside.\n");
    } else {
        printf("It's freezing outside.\n");
    }

    /* Nested conditions */
    const int x = 10;
    const int y = 20;

    if (x > 0) {
        if (y > 0) {
            printf("Both x and y are positive.\n");
        } else {
            printf("x is positive but y is not.\n");
        }
    }

    /* Conditions are just expressions -- any non-zero is true */
    if (x) {
        printf("x (%d) is truthy; only 0 is false in C.\n", x);
    }

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * In C, a condition is true when it evaluates to any non-zero
 * value and false when it evaluates to zero.  This means you
 * can test an int directly:  if (count)  instead of
 * if (count != 0).  Both are correct, but the shorter form
 * is idiomatic C.
 * ============================================================
 */


// 💡 Thinking in C:
// if/else is the most basic decision. In C, "truthy" means non-zero, "falsy" means zero.
