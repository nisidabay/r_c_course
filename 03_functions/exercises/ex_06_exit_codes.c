/*
 * Exercise 06: Exit Codes — EXIT_SUCCESS, EXIT_FAILURE
 *
 * Concept: main() returns an int to the OS. Convention: 0 (EXIT_SUCCESS)
 *          = success, nonzero (EXIT_FAILURE) = failure. Functions can also
 *          return error codes that main propagates.
 *
 * Fill in the blanks to complete a program that divides two integers safely.
 * Define a function 'safe_divide' that returns 0 on success, 1 on error.
 * main() should call it and return EXIT_SUCCESS or EXIT_FAILURE accordingly.
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

/*@*/
/* Define safe_divide: takes int a and int b, prints result, returns
 * 0 on success, 1 if b == 0 (division by zero) */
int safe_divide(int a, int b)
{
    /*@*/
    if (b /*@*/ 0) {
        printf("Error: division by zero!\n");
        return /*@*/;
    }

    printf("%d / %d = %d\n", a, b, a /*@*/ b);
    return /*@*/;
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
    /*@*/
    int result = /*@*/;

    if (result != 0) {
        printf("Operation failed. ");
        /*@*/
        return /*@*/;
    }

    printf("Operation succeeded. ");
    /*@*/
    return /*@*/;
}
