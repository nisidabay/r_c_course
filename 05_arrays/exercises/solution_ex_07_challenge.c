/*
 * ex_07_challenge.c — SOLUTION
 * Group 05 — Arrays
 * Mini-challenge: combine arrays, sizeof trick, and sorting
 *
 * Prompts for numbers until -1, sorts them, prints array + median.
 */

#include <stdio.h>

#define MAX_NUMBERS 100

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
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
    int numbers[MAX_NUMBERS];
    int count = 0;
    char buf[64];

    printf("Enter integers (one per line, -1 to stop):\n");

    while (count < MAX_NUMBERS) {
        int val;

        printf("> ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            break;
        }

        if (sscanf(buf, "%d", &val) != 1) {
            printf("Invalid input, try again.\n");
            continue;
        }

        if (val == -1) {
            break;
        }

        numbers[count] = val;
        count++;
    }

    if (count == 0) {
        printf("No numbers entered.\n");
        return 0;
    }

    /* Sort */
    selection_sort(numbers, count);

    /* Print sorted array */
    printf("\nSorted: ");
    for (int i = 0; i < count; ++i) {
        printf("%d ", numbers[i]);
    }
    putchar('\n');

    /* Compute median */
    double median;
    if (count % 2 == 1) {
        median = numbers[count / 2];
    } else {
        int mid = count / 2;
        median = (numbers[mid - 1] + numbers[mid]) / 2.0;
    }

    printf("Median: %.1f\n", median);

    return 0;
}
