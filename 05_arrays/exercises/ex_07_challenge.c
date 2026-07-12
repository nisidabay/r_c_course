/*
 * ex_07_challenge.c
 * Group 05 — Arrays
 * Mini-challenge: combine arrays, sizeof trick, and sorting
 *
 * Write a program that:
 *   1. Prompts the user for numbers (fgets + strtol) until they enter -1
 *   2. Stores them in a fixed-size int array (max 100 elements)
 *   3. Uses the sizeof trick to track elements added (or a counter)
 *   4. Sorts the array (selection sort) — YOU implement swap and selection_sort
 *   5. Prints the sorted array
 *   6. Finds and prints the minimum value in the sorted array
 *
 * No banned functions. Use fgets + strtol for all input.
 * Compiles with -std=c11. int main(void).
 * Use EXIT_SUCCESS / EXIT_FAILURE.
 *
 * HINTS:
 *   - Let the user enter up to 100 numbers.
 *   - Stop reading when the user enters -1 (do NOT store -1).
 *   - After input, sort the array using selection sort.
 *   - The minimum value in a sorted array is just the first element!
 *   - For input validation: fgets + strcspn + strtol (see group 03 examples).
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 100

/* Swap the values at two int pointers. */
/* NOTE: forward declaration needed because selection_sort() calls swap(). */
void swap(int *a, int *b);

void swap(int *a, int *b)
{
    (void)a;
    (void)b;
    // FIX ME
}

/* Sort arr[0..n-1] in ascending order using selection sort. */
void selection_sort(int arr[], int n)
{
    (void)arr;
    (void)n;
    // FIX ME
}

int main(void)
{
    int numbers[MAX_NUMBERS];
    size_t count = 0;
    char buf[64];

    printf("Enter numbers (one per line, -1 to stop):\n");

    /* Read until -1 or MAX_NUMBERS reached */
    while (count < MAX_NUMBERS) {
        printf("> ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            break;  /* EOF */
        }
        buf[strcspn(buf, "\n")] = '\0';

        char *endptr;
        errno = 0;
        long val = strtol(buf, &endptr, 10);
        if (endptr == buf || *endptr != '\0') {
            fprintf(stderr, "Invalid input, try again.\n");
            continue;
        }
        if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Number out of range, try again.\n");
            continue;
        }

        if (val == -1) {
            break;
        }

        numbers[count] = (int)val;
        count++;
    }

    if (count == 0) {
        printf("No numbers entered. Goodbye.\n");
        return EXIT_SUCCESS;
    }

    /* Sort the array */
    selection_sort(numbers, (int)count);

    /* Print sorted array */
    printf("Sorted array (%zu elements):", count);
    for (size_t i = 0; i < count; i++) {
        printf(" %d", numbers[i]);
    }
    printf("\n");

    /* Find minimum value (first element after sorting) */
    int min_val = numbers[0];  // FIX ME — this works only if sorted correctly
    printf("Minimum value: %d\n", min_val);
    printf("Minimum value (second version, just for practice):");

    // NOTE: find_min using array indexing was NOT taught as a separate
    // concept, but the logic follows from loops + if statements (group 03)
    // and array indexing (group 05).
    int found_min = numbers[0];
    for (size_t i = 1; i < count; i++) {
        if (numbers[i] < found_min) {
            found_min = numbers[i];
        }
    }
    printf(" %d\n", found_min);

    return EXIT_SUCCESS;
}
