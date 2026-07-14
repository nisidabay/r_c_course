/*
 * ex_03_null_pointer.c
 * Group 06 — Pointers 101
 * Exercise 03: NULL pointer as a sentinel — safe vs unsafe dereference
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * Always check for NULL before dereferencing a pointer.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int  value = 100;
    int *p      = &value;   /* valid pointer */
    int *nowhere = NULL;   /* points to nothing — use NULL */  // FIX ME

    /* 1. SAFE dereference: check p before using it */
    if (p != NULL) {  // FIX ME
        printf("p is valid, *p = %d\n", *p);
    } else {
        printf("p is NULL — should not happen here\n");
    }

    /* 2. Check 'nowhere' before dereferencing — it is NULL! */
    if (nowhere != NULL) {  // FIX ME
        printf("*nowhere = %d\n", *nowhere);
    } else {
        printf("nowhere is NULL — skipping dereference, program stays safe.\n");
    }

    /* 3. Complete the printf to explain what would happen without the check */
    printf("Without the if-check, *nowhere would cause a segfault.\n");  // FIX ME

    return EXIT_SUCCESS;
}

/*
 * After filling the blanks:
 *   NULL means "points to nothing" — never dereference it.
 *   Always check p != NULL before *p.
 *   Without the guard, dereferencing NULL crashes with a segfault.
 */
