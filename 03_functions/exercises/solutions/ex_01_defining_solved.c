/*
 * Exercise 01: Defining Functions — SOLUTION
 *
 * Every function needs: a return type, a name, a parameter list, and a body.
 */

#include <stdio.h>
#include <stdlib.h>

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
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &num) != 1)
        return 1;

    /* call say_hello */
    say_hello();

    /* call double_it with num, store the result, print it */
    int result = double_it(num);
    printf("double_it(%d) = %d\n", num, result);

    return 0;
}
