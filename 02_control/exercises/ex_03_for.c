/*
 * Exercise 03: For Loops
 *
 * Concept: A for loop collects initialization, condition, and increment
 *          in a single line: for (init; condition; increment) { body }
 *
 * Fill in the blanks to complete a program that reads an integer n (>= 1)
 * and prints the sum 1 + 2 + ... + n.
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int n;
    int sum = 0;

    printf("Enter a positive integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &n) != 1 || n < 1)
        return 1;

    /*@*/
    for (int i = /*@*/; i /*@*/ n; i++) {
        sum /*@*/ i;
    }

    printf("Sum = %d\n", sum);

    return 0;
}
