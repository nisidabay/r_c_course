/*
 * ex_05_sizeof_trick.c
 * Group 05 — Arrays
 * Exercise 05: the sizeof trick for array length
 *
 * Fill in the blanks (marked with /* @FILL_ME */) to complete the program.
 * Use sizeof to compute array element counts at compile time.
 */

#include <stdio.h>
#include <stddef.h>    /* size_t */

/*
 * A helper function that prints array elements.
 * Since the array decays to a pointer here, we must pass the length.
 */
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
    size_t count = sizeof(/* @FILL_ME */) / sizeof(/* @FILL_ME */);
    printf("Array has %zu elements (expected: 12)\n", count);

    /* 2. Print all elements using the computed count */
    printf("Measurements: ");
    for (size_t i = 0; i < count; ++i) {
        printf("%d ", measurements[i]);
    }
    putchar('\n');

    /* 3. Use the print_ints helper with the computed count */
    printf("Via helper:   ");
    print_ints(/* @FILL_ME */, /* @FILL_ME */);

    /* 4. Compute total bytes vs element bytes */
    printf("sizeof(measurements) = %zu bytes\n", sizeof(/* @FILL_ME */));
    printf("sizeof(measurements[0]) = %zu bytes\n", sizeof(/* @FILL_ME */));

    return 0;
}

/*
 * After filling the blanks:
 *   count should be 12
 *   sizeof(measurements) should be 48 (12 × 4 bytes per int)
 *   sizeof(measurements[0]) should be 4
 */
