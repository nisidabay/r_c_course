/*
 * ex_06_sorting.c — SOLUTION
 * Group 05 — Arrays
 * Exercise 06: sorting an array (selection sort)
 */

#include <stdio.h>

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void print_array(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

static void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&arr[i], &arr[min_idx]);
        }
    }
}

int main(void) {
    int scores[8] = { 42, 17, 55, 8, 31, 99, 63, 24 };
    int n = 8;

    printf("Before: ");
    print_array(scores, n);

    selection_sort(scores, n);

    printf("After:  ");
    print_array(scores, n);

    return 0;
}
