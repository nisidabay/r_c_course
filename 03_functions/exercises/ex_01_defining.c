/*
 * Exercise 01: Defining Functions
 *
 * Concept: Every function needs a return type, a name, a parameter list,
 *          and a body. Syntax: return_type name(param_type param_name, ...) { body }
 *
 * Fill in the blanks (marked /*@*//*@*/) to complete the program.
 * The program should define a function called 'double_it' that takes an int
 * and returns twice that value, and a function called 'say_hello' that prints
 * "Hello from say_hello!" (takes nothing, returns nothing).
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

/*@*/
/* Define a void function called say_hello that prints "Hello from say_hello!" */
void say_hello(/*@*/)
{
    /*@*/
}

/*@*/
/* Define a function called double_it that takes an int n and returns int */
/*@*/ /*@*/(/*@*/)
{
    /*@*/
}

int main(void) {
    char buf[BUFSZ];
    int num;

    printf("Enter an integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &num) != 1)
        return 1;

    /*@*/
    /* call say_hello */
    /*@*/

    /*@*/
    /* call double_it with num, store the result, print it */
    int result = /*@*/;
    printf("double_it(%d) = %d\n", num, result);

    return 0;
}
