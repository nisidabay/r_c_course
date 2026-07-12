/*
 * ex_02_function_pointers.c
 * Group 10 — Advanced
 * Exercise 02: function pointers
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * Read the comments to understand what each line should do.
 */

#include <stdio.h>
#include <stdlib.h>

/* ---------- two operation functions ---------- */
int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }
int subtract(int a, int b) { return a - b; }   /* subtract */  // FIX ME

/* ---------- apply a function pointer over an array ---------- */
int reduce(int *arr, size_t n, int init, int (*op)(int, int)) {  // FIX ME
    int result = init;
    for (size_t i = 0; i < n; i++) {
        result = op(result, arr[i]);  // FIX ME
    }
    return result;
}

int main(void) {
    int data[] = { 1, 2, 3, 4, 5 };
    size_t n = sizeof data / sizeof data[0];

    /* DECLARE a function pointer named 'fn' */
    int (*fn)(int, int) = NULL;  // FIX ME

    /* ASSIGN it to the add function */
    fn = add;  // FIX ME

    int sum = reduce(data, n, 0, fn);
    printf("Sum: %d (expected: 15)\n", sum);

    /* Re-assign to mul */
    fn = mul;  // FIX ME
    int product = reduce(data, n, 1, fn);
    printf("Product: %d (expected: 120)\n", product);

    /* Try with subtract */
    fn = subtract;
    int diff = reduce(data, n, 0, fn);
    printf("Diff (0-1-2-3-4-5): %d (expected: -15)\n", diff);

    return EXIT_SUCCESS;
}
