/*
 * 05_sizeof_trick.c
 * Group 05 — Arrays
 * Concept: computing array length at compile time with sizeof
 *
 * sizeof(arr) gives total bytes; sizeof(arr[0]) gives bytes per element.
 * Dividing them yields the element count.
 * This works ONLY on the actual array — NOT on a pointer parameter.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>    /* size_t */

/* Function that receives an array as a parameter — it decays to a pointer */
void print_array(int arr[], size_t count) {
    size_t i;
    printf("Inside function: sizeof(arr) = %zu bytes (pointer size)\n", sizeof(arr));
    for (i = 0; i < count; ++i) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main(void) {
    int scores[10] = { 85, 92, 78, 91, 88, 76, 95, 89, 84, 90 };
    size_t count = sizeof(scores) / sizeof(scores[0]);

    printf("sizeof(scores)       = %zu bytes\n", sizeof(scores));
    printf("sizeof(scores[0])    = %zu bytes\n", sizeof(scores[0]));
    printf("Array length         = %zu elements\n\n", count);

    /* Works here — scores is the real array */
    size_t i;
    printf("All scores: ");
    for (i = 0; i < count; ++i) {
        printf("%d ", scores[i]);
    }
    putchar('\n');

    /* Passing to a function — must pass length separately */
    printf("\nPrinting via function:\n");
    print_array(scores, count);

    return EXIT_SUCCESS;
}
/*
 * Thinking in C:
 * sizeof on an array is a compile-time constant — no runtime cost.
 * When passed to a function, the array "decays" to a pointer;
 * sizeof then reports the pointer size, not the array.
 * Rule: if you need the length in a function, pass it as a parameter.
 */