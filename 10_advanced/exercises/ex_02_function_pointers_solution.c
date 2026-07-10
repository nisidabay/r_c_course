/*
 * ex_02_function_pointers_solution.c
 * Group 10 — Advanced
 * Exercise 02: function pointers — SOLUTION
 */

#include <stdio.h>
#include <stdlib.h>

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }
int sub(int a, int b) { return a - b; }

int reduce(int *arr, size_t n, int init, int (*op)(int, int)) {
    int result = init;
    for (size_t i = 0; i < n; i++) {
        result = op(result, arr[i]);
    }
    return result;
}

int main(void) {
    int data[] = { 1, 2, 3, 4, 5 };
    size_t n = sizeof data / sizeof data[0];

    int (*fn)(int, int) = NULL;

    fn = add;
    int sum = reduce(data, n, 0, fn);
    printf("Sum: %d (expected: 15)\n", sum);

    fn = mul;
    int product = reduce(data, n, 1, fn);
    printf("Product: %d (expected: 120)\n", product);

    fn = sub;
    int diff = reduce(data, n, 0, fn);
    printf("Diff (0-1-2-3-4-5): %d (expected: -15)\n", diff);

    return 0;
}
