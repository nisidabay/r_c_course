/*
 * 04_pointers_params.c — pass-by-value FAILS, pointers SUCCEED
 *
 * KEY LEARNING MOMENT. This file demonstrates the single most important
 * reason C has pointers: to let functions modify variables at the caller.
 *
 * Part A: A function that tries to swap two ints via parameters.
 *          C copies arguments — the swap is local, the caller sees nothing.
 * Part B: A function that swaps via POINTERS. Because the function gets
 *          addresses, it modifies the ORIGINAL variables.
 * Part C: Why — C is pass-by-value. Pointers pass the address so the callee
 *          can reach the caller's memory.
 */

#include <stdio.h>
#include <stdlib.h>

/* -- PART A: swap that FAILS (pass-by-value) -- */
void swap_fails(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
    printf("  Inside swap_fails: a=%d, b=%d  (swapped locally)\n", a, b);
}

/* -- PART B: swap that WORKS (pointers) -- */
void swap_works(int *a, int *b)
{
    int temp = *a;   /* read value at address a */
    *a = *b;         /* write value from b's address into a's address */
    *b = temp;       /* write saved temp into b's address */
}

int main(void)
{
    int x = 10;
    int y = 20;

    /* -- Demonstrate FAIL first -- */
    printf("=== PASS-BY-VALUE FAILS ===\n");
    printf("Before swap_fails:  x=%d, y=%d\n", x, y);
    swap_fails(x, y);
    printf("After  swap_fails:  x=%d, y=%d\n", x, y);
    printf("  → x and y are UNCHANGED. swap_fails only swapped copies.\n\n");

    /* -- Demonstrate pointer solution -- */
    printf("=== POINTERS FIX IT ===\n");
    printf("Before swap_works: x=%d, y=%d\n", x, y);
    swap_works(&x, &y);   /* pass ADDRESSES, not copies */
    printf("After  swap_works: x=%d, y=%d\n", x, y);
    printf("  → x and y ARE swapped. swap_works modified the originals.\n\n");

    /* -- WHY -- */
    printf("=== WHY? ===\n");
    printf("C always copies arguments. swap_fails(x,y) copies 10 and 20\n");
    printf("into the parameters a,b — swapping a,b does nothing to x,y.\n");
    printf("swap_works(&x,&y) copies the ADDRESSES. *a = *b writes through\n");
    printf("the pointer, reaching the original x and y in main's memory.\n");
    printf("The pointer is just a number (an address) on the stack, but\n");
    printf("that number lets the function reach OUTSIDE its own frame.\n");

    return EXIT_SUCCESS;
}

/*
 * Thinking in C:
 *   C passes everything by value — the callee gets a COPY.
 *   Without pointers, a function CANNOT modify its caller's variables.
 *   A pointer parameter copies the address, not the data.
 *   Dereferencing (*a) reads/writes the CALLER'S memory through that address.
 *   This is the KEY insight: pointers give functions access to your data.
 */
