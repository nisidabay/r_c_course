/*
 * ex_02_function_pointers.c
 * Group 10 — Advanced
 * Exercise 02: function pointers
 *
 * Fill in the blanks (marked with /* @FILL_ME */) to complete the program.
 * Read the comments to understand what each line should do.
 */

#include <stdio.h>
#include <stdlib.h>

/* ---------- two operation functions ---------- */
int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }
int /* @FILL_ME */ (int a, int b) { return a - b; }   /* subtract */

/* ---------- apply a function pointer over an array ---------- */
int reduce(int *arr, size_t n, int init, /* @FILL_ME */) {
    int result = init;
    for (size_t i = 0; i < n; i++) {
        /* @FILL_ME */ = op(result, arr[i]);
    }
    return result;
}

int main(void) {
    int data[] = { 1, 2, 3, 4, 5 };
    size_t n = sizeof data / sizeof data[0];

    /* DECLARE a function pointer named 'fn' */
    /* @FILL_ME */ = NULL;

    /* ASSIGN it to the add function */
    /* @FILL_ME */ = add;

    int sum = reduce(data, n, 0, fn);
    printf("Sum: %d (expected: 15)\n", sum);

    /* Re-assign to mul */
    fn = /* @FILL_ME */;
    int product = reduce(data, n, 1, fn);
    printf("Product: %d (expected: 120)\n", product);

    /* Try with -D STDC_WANT_LIB_EXT1 subtract */
    fn = subtract;
    int diff = reduce(data, n, 0, fn);
    printf("Diff (0-1-2-3-4-5): %d (expected: -15)\n", diff);

    return 0;
}
