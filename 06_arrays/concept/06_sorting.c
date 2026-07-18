/*
 * 06_sorting.c
 * Group 05 — Arrays
 * Concept: in-place selection sort on an int array
 *
 * Selection sort: find the smallest element in the unsorted portion
 * and swap it into position.  O(n²) but simple and easy to verify.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Swap two integers via pointers — the standard C idiom.
 */
static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/*
 * Selection sort: repeatedly extract the minimum element.
 * 'n' is the number of elements in the array.
 */
static void selection_sort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&arr[i], &arr[min_idx]);
        }
    }
}

static void print_array(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main(void) {
    int temps[10] = { 31, 18, 42, 27, 35, 22, 29, 40, 33, 25 };
    int n = 10;

    printf("Before sort: ");
    print_array(temps, n);

    selection_sort(temps, n);

    printf("After sort:  ");
    print_array(temps, n);

    return EXIT_SUCCESS;
}
/*
 * Thinking in C:
 * Sorting modifies the array in place — no copy needed.
 * The swap helper uses pointers because C passes by value.
 * Understanding selection sort builds the pattern-matching
 * intuition needed for binary search, merge, and quicksort.
 */