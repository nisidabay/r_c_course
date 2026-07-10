/*
 * ex_07_challenge.c
 * Group 05 — Arrays
 * Mini-challenge: combine arrays, sizeof trick, and sorting
 *
 * Write a program that:
 *   1. Prompts the user for numbers (fgets + sscanf) until they enter -1
 *   2. Stores them in a fixed-size int array (max 100 elements)
 *   3. Uses the sizeof trick to track elements added (or a counter)
 *   4. Sorts the array (selection sort)
 *   5. Prints the sorted array and the median value
 *
 * No banned functions. Use fgets + sscanf for all input.
 * Compiles with -std=c11. int main(void).
 *
 * HINTS:
 *   - Let the user enter up to 100 numbers.
 *   - Stop reading when the user enters -1 (do NOT store -1).
 *   - After input, sort the array using selection sort.
 *   - If the count is odd, median = middle element.
 *   - If the count is even, median = average of two middle elements.
 */

#include <stdio.h>

/* Write your swap function here */
static void swap(int *a, int *b) {
    /* YOUR CODE */
}

/* Write your selection_sort function here */
static void selection_sort(int arr[], int n) {
    /* YOUR CODE */
}

int main(void) {
    /* YOUR CODE */

    return 0;
}
