/*
 * ex_05_arrays_pointers.c
 * Group 06 — Pointers 101
 * Exercise 05: array decay and pointer arithmetic
 *
 * Fill in the blanks (marked with /* @FILL_ME */) to complete the program.
 * Understand that arr[i] is syntactic sugar for *(arr + i).
 */

#include <stdio.h>

int main(void) {
    int arr[] = { 10, 20, 30, 40, 50 };
    int len   = sizeof(arr) / sizeof(arr[0]);

    /* 1. Show that arr decays to &arr[0] */
    printf("arr                   = %p\n", (void *)arr);
    printf("&arr[0]               = %p\n", (void *) /* @FILL_ME */);

    /* 2. Pointer arithmetic: make p point to arr[0], then show p+1, p+2 */
    int *p = arr;   /* p points to arr[0] */
    printf("p           = %p\n", (void *)p);
    printf("p + 1       = %p\n", (void *)(p /* @FILL_ME */));
    printf("p + 2       = %p\n", (void *)(p + 2));
    printf("sizeof(int) = %zu bytes\n\n", sizeof(int));

    /* 3. Prove arr[i] == *(arr + i) for every element */
    printf("=== arr[i] == *(arr + i) ===\n");
    for (int i = 0; i < len; i++) {
        int via_brackets  = arr[i];
        int via_arith     = *(arr /* @FILL_ME */ i);
        printf("arr[%d] = %d    *(arr + %d) = %d    %s\n",
               i, via_brackets,
               i, via_arith,
               via_brackets == via_arith ? "equal" : "MISMATCH");
    }

    /* 4. Write through pointer arithmetic (set arr[2] to 300) */
    printf("\n=== Writing through pointer arithmetic ===\n");
    /* @FILL_ME */ = 300;   /* same as arr[2] = 300 */
    printf("After *(arr + 2) = 300:\n");
    for (int i = 0; i < len; i++) {
        printf("  arr[%d] = %d\n", i, arr[i]);
    }

    return 0;
}

/*
 * After filling the blanks:
 *   &arr[0] gives the same address as arr.
 *   p + 1 advances by sizeof(int) bytes.
 *   arr[i] == *(arr + i) for all i.
 *   *(arr + 2) = 300 is identical to arr[2] = 300.
 */
