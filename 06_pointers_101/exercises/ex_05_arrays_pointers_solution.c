/*
 * ex_05_arrays_pointers.c — SOLUTION
 * Group 06 — Pointers 101
 * Exercise 05: array decay and pointer arithmetic
 */

#include <stdio.h>

int main(void) {
    int arr[] = { 10, 20, 30, 40, 50 };
    int len   = sizeof(arr) / sizeof(arr[0]);

    /* 1. Show that arr decays to &arr[0] */
    printf("arr                   = %p\n", (void *)arr);
    printf("&arr[0]               = %p\n", (void *)&arr[0]);

    /* 2. Pointer arithmetic */
    int *p = arr;
    printf("p           = %p\n", (void *)p);
    printf("p + 1       = %p\n", (void *)(p + 1));
    printf("p + 2       = %p\n", (void *)(p + 2));
    printf("sizeof(int) = %zu bytes\n\n", sizeof(int));

    /* 3. Prove arr[i] == *(arr + i) */
    printf("=== arr[i] == *(arr + i) ===\n");
    for (int i = 0; i < len; i++) {
        int via_brackets  = arr[i];
        int via_arith     = *(arr + i);
        printf("arr[%d] = %d    *(arr + %d) = %d    %s\n",
               i, via_brackets,
               i, via_arith,
               via_brackets == via_arith ? "equal" : "MISMATCH");
    }

    /* 4. Write through pointer arithmetic */
    printf("\n=== Writing through pointer arithmetic ===\n");
    *(arr + 2) = 300;
    printf("After *(arr + 2) = 300:\n");
    for (int i = 0; i < len; i++) {
        printf("  arr[%d] = %d\n", i, arr[i]);
    }

    return 0;
}
