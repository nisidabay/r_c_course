/*
 * 03_null_pointer.c — NULL as a sentinel, safe vs unsafe dereference
 *
 * A pointer that does not point to valid memory should be set to NULL
 * (from <stddef.h>). Dereferencing a NULL pointer crashes the program
 * (segmentation fault). Always check for NULL before dereferencing.
 *
 * NULL == 0 in value; it is the one address that is guaranteed NOT
 * to be a valid variable. Think of it as "points to nothing."
 */

#include <stdio.h>
#include <stddef.h>   /* NULL */

int main(void)
{
    int  value = 100;
    int *p      = &value;   /* valid pointer */
    int *nowhere = NULL;    /* points to nothing */

    /* -- SAFE: p points to valid memory -- */
    if (p != NULL) {
        printf("p is valid, *p = %d\n", *p);
    }

    /* -- UNSAFE: dereferencing NULL crashes -- */
    printf("About to dereference NULL...\n");

    if (nowhere != NULL) {
        printf("*nowhere = %d\n", *nowhere);
    } else {
        printf("nowhere is NULL — skipping dereference, program stays safe.\n");
    }

    /* -- What would happen without the check (commented out) -- */
    /* int crash = *nowhere;   <-- segmentation fault, program dies */

    printf("Program finished safely because we checked before using.\n");

    return 0;
}

/*
 * Thinking in C:
 *   NULL means "points to nothing" — never dereference it.
 *   Always check p != NULL before *p; one check prevents a crash.
 *   NULL comes from <stddef.h> (or <stdio.h>); it is the safe default
 *   for any pointer that isn't yet pointing to real data.
 */
