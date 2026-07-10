/*
 * Exercise 04: Scope — Local vs Global Variables
 *
 * Concept: "Scope" is where a variable is visible. Global scope = visible
 *          everywhere. Local/block scope = visible only inside { } where
 *          declared. Inner scopes can shadow outer names.
 *
 * Fill in the blanks to complete a program that uses a global counter,
 * a local variable, and a block scope to demonstrate visibility rules.
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

/*@*/
/* Declare a global int called counter, initialized to 0 */
/*@*/ int /*@*/ = 0;

/*@*/
/* Define increment_counter: adds 1 to the global counter, prints it */
void increment_counter(/*@*/)
{
    /*@*/
    counter = counter /*@*/ 1;
    printf("  Global counter is now: %d\n", /*@*/);
}

int main(void) {
    char buf[BUFSZ];
    int local_val;

    printf("Enter an integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &local_val) != 1)
        return 1;

    printf("Initial counter: %d\n", counter);
    printf("Initial local_val: %d\n", local_val);

    increment_counter();
    increment_counter();

    printf("After 2 increments, counter = %d\n", counter);

    /*@*/
    /* Block scope: create a new int called local_val that shadows the outer one */
    {
        int /*@*/ = 999;
        printf("Inside block: local_val = %d\n", local_val);
    }

    printf("Outside block: local_val = %d (original restored)\n", local_val);

    return 0;
}
