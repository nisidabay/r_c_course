/*
 * Exercise 03: Pass by Value — SOLUTION
 *
 * Arguments are ALWAYS copied into the function's parameters.
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

/* Define triple: takes int n, multiplies by 3, prints local value, returns nothing */
void triple(int n)
{
    n = n * 3;
    printf("  Inside triple: n = %d\n", n);
}

/* Define add_them: takes int a and int b, returns their sum */
int add_them(int a, int b)
{
    return a + b;
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
    triple(x);
    printf("After triple:  x = %d (unchanged!)\n", x);

    int sum = add_them(x, y);
    printf("add_them(%d, %d) = %d\n", x, y, sum);

    return 0;
}
