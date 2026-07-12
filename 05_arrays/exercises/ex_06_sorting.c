/*
 * ex_06_sorting.c
 * Group 05 — Arrays
 * Exercise 06: sorting an array (selection sort)
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * Implement the helper functions and the main sort logic.
 */

#include <stdio.h>
#include <stdlib.h>

/* Swap two integers via pointers */
static void swap(int *a, int *b) {
    int tmp = *a;  // FIX ME
    *a = *b;
    *b = tmp;  // FIX ME
}

/* Print an array of n integers */
static void print_array(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

/* Selection sort: sort arr (with n elements) in ascending order */
static void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {  // FIX ME
                min_idx = j;
            }
        }
        if (min_idx != i) {  // FIX ME
            swap(&arr[i], &arr[min_idx]);
        }
    }
}

int main(void) {
    int scores[8] = { 42, 17, 55, 8, 31, 99, 63, 24 };
    int n = 8;

    printf("Before: ");
    print_array(scores, n);  // FIX ME

    selection_sort(scores, n);  // FIX ME

    printf("After:  ");
    print_array(scores, n);

    return EXIT_SUCCESS;
}

/*
 * After filling the blanks:
 *   Before: 42 17 55 8 31 99 63 24
 *   After:  8 17 24 31 42 55 63 99
 */
