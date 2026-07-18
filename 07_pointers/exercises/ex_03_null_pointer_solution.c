/*
 * ex_03_null_pointer.c — SOLUTION
 * Group 06 — Pointers 101
 * Exercise 03: NULL pointer as a sentinel — safe vs unsafe dereference
 */

#include <stdio.h>
#include <stddef.h>

int main(void) {
    int  value = 100;
    int *p      = &value;   /* valid pointer */
    int *nowhere = NULL;    /* points to nothing */

    /* 1. SAFE dereference: check p before using it */
    if (p != NULL) {
        printf("p is valid, *p = %d\n", *p);
    } else {
        printf("p is NULL — should not happen here\n");
    }

    /* 2. Check 'nowhere' before dereferencing */
    if (nowhere != NULL) {
        printf("*nowhere = %d\n", *nowhere);
    } else {
        printf("nowhere is NULL — skipping dereference, program stays safe.\n");
    }

    /* 3. Explain what would happen without the check */
    printf("Without the if-check, *nowhere would cause a segmentation fault.\n");

    return 0;
}
