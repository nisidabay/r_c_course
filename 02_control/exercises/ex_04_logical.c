/*
 * Exercise 04: Logical Operators (&&, ||, !)
 *
 * Concept: Combine boolean expressions with && (AND), || (OR), and ! (NOT).
 *
 * Fill in the blanks to complete a program that reads an integer and prints
 * whether it is in the range [10, 50] inclusive.
 *
 * Hint: Use logical AND (&&) to check both bounds.
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int num;
    bool in_range;

    printf("Enter an integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &num) != 1)
        return 1;

    /*@*/
    in_range = (num /*@*/ 10) /*@*/ (num /*@*/ 50);

    if (in_range) {
        printf("In range\n");
    } else {
        printf("Out of range\n");
    }

    return 0;
}
