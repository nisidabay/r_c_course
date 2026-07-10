/*
 * Exercise 03: Pass by Value
 *
 * Concept: In C, arguments are ALWAYS copied into the function's parameters.
 *          The function works on its own copies — changes inside the function
 *          do NOT affect the original variables in the caller.
 *
 * Fill in the blanks to complete a program that demonstrates pass-by-value.
 * Define a function 'triple' that takes an int, multiplies it by 3 inside,
 * and prints the local value. Then in main, show that the original is unchanged.
 * Also define a function 'add_them' that takes two ints and returns their sum.
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

/*@*/
/* Define triple: takes int n, multiplies by 3, prints local value, returns nothing */
void triple(/*@*/)
{
    /*@*/
    n = n /*@*/ 3;
    printf("  Inside triple: n = %d\n", n);
    /*@*/
}

/*@*/
/* Define add_them: takes int a and int b, returns their sum */
int add_them(/*@*/)
{
    return /*@*/;
}

int main(void) {
    char buf[BUFSZ];
    int x, y;

    printf("Enter two integers separated by space: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d %d", &x, &y) != 2)
        return 1;

    printf("Before triple: x = %d\n", x);
    triple(/*@*/);
    printf("After triple:  x = %d (unchanged!)\n", x);

    int sum = add_them(/*@*/, /*@*/);
    printf("add_them(%d, %d) = %d\n", x, y, sum);

    return 0;
}
