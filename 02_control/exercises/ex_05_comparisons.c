/*
 * Exercise 05: Comparisons (==, !=, <, >, <=, >=)
 *
 * Concept: Comparison operators produce boolean results (0 or 1).
 *          ==  equal to
 *          !=  not equal to
 *          <   less than
 *          >   greater than
 *          <=  less than or equal to
 *          >=  greater than or equal to
 *
 * Fill in the blanks to complete a program that reads two integers a and b
 * and prints:
 *   "a is greater"   if a > b
 *   "b is greater"   if a < b
 *   "equal"          if a == b
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int a, b;

    printf("Enter two integers (space-separated): ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d %d", &a, &b) != 2)
        return 1;

    if (a /*@*/ b) {
        printf("a is greater\n");
    /*@*/
    } if (a /*@*/ b) {
        printf("b is greater\n");
    } /*@*/ {
        printf("equal\n");
    }

    return 0;
}
