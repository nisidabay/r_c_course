/*
 * Exercise 06: Exit Codes — SOLUTION
 *
 * main() returns an int to the OS. Use EXIT_SUCCESS and EXIT_FAILURE.
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

/* Define safe_divide: takes int a and int b, prints result, returns
 * 0 on success, 1 if b == 0 (division by zero) */
int safe_divide(int a, int b)
{
    if (b == 0) {
        printf("Error: division by zero!\n");
        return 1;
    }

    printf("%d / %d = %d\n", a, b, a / b);
    return 0;
}

int main(void) {
    char buf[BUFSZ];
    int x, y;
    int status = 0;

    printf("Enter two integers (numerator and denominator): ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d %d", &x, &y) != 2)
        return 1;

    /* call safe_divide and capture its return value */
    int result = safe_divide(x, y);

    if (result != 0) {
        printf("Operation failed. ");
        return EXIT_FAILURE;
    }

    printf("Operation succeeded. ");
    return EXIT_SUCCESS;
}
