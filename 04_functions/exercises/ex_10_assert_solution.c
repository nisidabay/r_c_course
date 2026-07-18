/*
 * Exercise 10 — Assert (assert.h) — SOLUTION
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static double average(const int *arr, size_t n)
{
    assert(arr != NULL);
    assert(n > 0);

    int sum = 0;
    for (size_t i = 0; i < n; i++)
        sum += arr[i];
    return (double)sum / (double)n;
}

static int safe_divide(int a, int b)
{
    assert(b != 0);
    return a / b;
}

int main(void)
{
    int values[] = {10, 20, 30};

    printf("average({10, 20, 30}, 3) = %.1f\n", average(values, 3));
    printf("safe_divide(10, 2) = %d\n", safe_divide(10, 2));

    return EXIT_SUCCESS;
}
