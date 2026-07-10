/*
 * Exercise 05: Function Prototypes (Forward Declarations)
 *
 * Concept: A prototype tells the compiler about a function BEFORE its
 *          definition or use. Syntax: return_type name(param_types);
 *          Without prototypes, C assumes 'int' return — which is dangerous.
 *
 * Fill in the blanks to complete a program that has prototypes at the top,
 * uses them in main(), and defines the functions below main().
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

/* ---- function prototypes ---- */

/*@*/
/* Prototype for is_positive: takes int, returns int (1 if > 0, 0 otherwise) */
/*@*/ is_positive(/*@*/);

/*@*/
/* Prototype for multiply: takes two ints, returns int */
int /*@*/(int a, int b);

/*@*/
/* Prototype for print_status: takes int (the value) and int (the positive flag),
 * returns nothing */
void print_status(/*@*/, /*@*/);

int main(void) {
    char buf[BUFSZ];
    int x, y;

    printf("Enter two integers separated by space: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d %d", &x, &y) != 2)
        return 1;

    /* call is_positive on x */
    int pos_x = is_positive(/*@*/);
    print_status(x, /*@*/);

    /* call multiply */
    int prod = multiply(/*@*/, /*@*/);
    printf("%d * %d = %d\n", x, y, prod);

    return 0;
}

/* ---- function definitions (below main) ---- */

/*@*/
int is_positive(int n)
{
    if (/*@*/ > 0) {
        return 1;
    }
    return 0;
}

/*@*/
int multiply(int a, int b)
{
    return a /*@*/ b;
}

/*@*/
void print_status(int val, int is_pos)
{
    if (is_pos) {
        printf("%d is positive.\n", val);
    } else {
        printf("%d is NOT positive.\n", val);
    }
}
