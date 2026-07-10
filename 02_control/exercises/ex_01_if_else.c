/*
 * Exercise 01: If / Else
 *
 * Concept: Conditional execution with if, else if, and else.
 *
 * Fill in the blanks (marked /*@*//*@*/) to complete the program.
 * The program should read an integer and print:
 *   "positive" if > 0
 *   "negative" if < 0
 *   "zero" if == 0
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int num;

    printf("Enter an integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &num) != 1)
        return 1;

    /*@*/
    if (num > 0) {
        printf("positive\n");
    /*@*/
    } else if (/*@*/) {
        printf("negative\n");
    } /*@*/ {
        printf("zero\n");
    }

    return 0;
}
