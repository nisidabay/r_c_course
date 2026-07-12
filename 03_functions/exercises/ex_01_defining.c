/*
 * Exercise 01: Defining Functions
 *
 * Concept: Every function needs a return type, a name, a parameter list,
 *          and a body. Syntax: return_type name(param_type param_name, ...) { body }
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * The program should define a function called 'double_it' that takes an int
 * and returns twice that value, and a function called 'say_hello' that prints
 * "Hello from say_hello!" (takes nothing, returns nothing).
 *
 * Safe C Standard: use fgets + strtol (do NOT use scanf).
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

// FIX ME
/* Define a void function called say_hello that prints "Hello from say_hello!" */
void say_hello(void)  // FIX ME
{
    printf("Hello from say_hello!\n");  // FIX ME
}

// FIX ME
/* Define a function called double_it that takes an int n and returns int */
int double_it(int n)  // FIX ME  // FIX ME
{
    return n * 2;  // FIX ME
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

    say_hello();  // FIX ME
    /* call say_hello */
    // FIX ME

    // FIX ME
    /* call double_it with num, store the result, print it */
    int result = double_it(num);  // FIX ME
    printf("double_it(%d) = %d\n", num, result);

    return EXIT_SUCCESS;
}
