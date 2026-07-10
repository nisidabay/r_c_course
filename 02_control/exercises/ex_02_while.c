/*
 * Exercise 02: While Loops
 *
 * Concept: A while loop repeats a block while a condition is true.
 *
 * Fill in the blanks to complete a program that reads a positive integer n
 * and prints the numbers from n down to 1 (one per line).
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int n;

    printf("Enter a positive integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &n) != 1 || n <= 0)
        return 1;

    /*@*/
    /*@*/
    while (/*@*/) {
        printf("%d\n", i);
        /*@*/
    }

    return 0;
}
