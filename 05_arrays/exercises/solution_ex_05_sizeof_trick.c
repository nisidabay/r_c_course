/*
 * ex_05_sizeof_trick.c — SOLUTION
 * Group 05 — Arrays
 * Exercise 05: the sizeof trick for array length
 */

#include <stdio.h>
#include <stddef.h>    /* size_t */

static void print_ints(int arr[], size_t count) {
    for (size_t i = 0; i < count; ++i) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main(void) {
    int measurements[12] = { 101, 103, 107, 109, 113, 127,
                             131, 137, 139, 149, 151, 157 };

    /* 1. Compute the number of elements using the sizeof trick */
    size_t count = sizeof(measurements) / sizeof(measurements[0]);
    printf("Array has %zu elements (expected: 12)\n", count);

    /* 2. Print all elements using the computed count */
    printf("Measurements: ");
    for (size_t i = 0; i < count; ++i) {
        printf("%d ", measurements[i]);
    }
    putchar('\n');

    /* 3. Use the print_ints helper with the computed count */
    printf("Via helper:   ");
    print_ints(measurements, count);

    /* 4. Compute total bytes vs element bytes */
    printf("sizeof(measurements) = %zu bytes\n", sizeof(measurements));
    printf("sizeof(measurements[0]) = %zu bytes\n", sizeof(measurements[0]));

    return 0;
}
