/*
 * Exercise 01: Defining Functions — SOLUTION
 *
 * Every function needs: a return type, a name, a parameter list, and a body.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

/* Define a void function called say_hello that prints "Hello from say_hello!" */
void say_hello(void)
{
    printf("Hello from say_hello!\n");
}

/* Define a function called double_it that takes an int n and returns int */
int double_it(int n)
{
    return n * 2;
}

int main(void) {
    char buf[BUFSZ];
    int num;

    printf("Enter an integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    buf[strcspn(buf, "\n")] = '\0';

    char *endptr;
    errno = 0;
    long val = strtol(buf, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    if (endptr == buf || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Out of int range\n");
        return EXIT_FAILURE;
    }
    num = (int)val;

    /* call say_hello */
    say_hello();

    /* call double_it with num, store the result, print it */
    int result = double_it(num);
    printf("double_it(%d) = %d\n", num, result);

    return EXIT_SUCCESS;
}
