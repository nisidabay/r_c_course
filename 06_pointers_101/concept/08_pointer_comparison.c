/*
 * 08_pointer_comparison.c — Pointer arithmetic with while loop
 * Group 06 - Pointers 101
 *
 * When iterating over an array with pointers, the idiomatic pattern
 * uses pointer comparison:  ptr_current < ptr_end.
 *
 * This is clearer and often more efficient than indexing with [i].
 * It works because pointer arithmetic always respects element size.
 *
 * Shows find_min and find_max using this pattern.
 */

#include <stdio.h>
#include <stdlib.h>

/* ---- find minimum value using pointer comparison ---- */
int find_min(int *arr, size_t n)
{
    if (arr == NULL || n == 0) {
        return EXIT_SUCCESS;
    }

    int *ptr_min     = arr;
    int *ptr_current = arr;
    int *ptr_end     = arr + n;

    while (ptr_current < ptr_end) {
        if (*ptr_current < *ptr_min) {
            ptr_min = ptr_current;
        }
        ptr_current++;
    }
    return *ptr_min;
}

/* ---- find maximum value using pointer comparison ---- */
int find_max(int *arr, size_t n)
{
    if (arr == NULL || n == 0) {
        return EXIT_SUCCESS;
    }

    int *ptr_max     = arr;
    int *ptr_current = arr;
    int *ptr_end     = arr + n;

    while (ptr_current < ptr_end) {
        if (*ptr_current > *ptr_max) {
            ptr_max = ptr_current;
        }
        ptr_current++;
    }
    return *ptr_max;
}

int main(void)
{
    int numbers[] = {12, 34, 5, 88, -1};
    size_t size   = sizeof(numbers) / sizeof(numbers[0]);

    printf("Array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", *(numbers + i));
    }
    printf("\n");

    int min = find_min(numbers, size);
    int max = find_max(numbers, size);

    printf("Min: %d\n", min);
    printf("Max: %d\n", max);

    if (min == -1 && max == 88) {
        puts("All correct — pointer comparison works.");
    } else {
        puts("Something is wrong.");
    }

    return EXIT_SUCCESS;
}

// Thinking in C:
// arr + n computes the address one-past-the-end.  Comparing
// ptr_current < ptr_end is safe and idiomatic — C guarantees
// that a pointer one past the end of an array is valid for
// comparison.  Pointer arithmetic is element-aware: p+1 adds
// sizeof(*p) bytes, not 1 byte.  This is the foundation for
// all array traversal without indices.
