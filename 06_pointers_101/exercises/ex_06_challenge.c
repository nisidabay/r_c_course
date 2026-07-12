/*
 * ex_06_challenge.c
 * Group 06 — Pointers 101
 * Challenge: pointer params + arrays + pointer arithmetic
 *
 * This challenge combines everything from Group 06:
 *   - Pointer parameters (swap via &)
 *   - Array/pointer equivalence (arr[i] == *(arr + i))
 *   - Pointer arithmetic (p++, *(p + n))
 *
 * Fill in the blanks (marked FIX ME) to implement three functions:
 *   1. array_print  — prints an array using pointer arithmetic
 *   2. array_sum    — computes sum using pointer arithmetic
 *   3. array_reverse — reverses array in-place using a swap helper
 *   4. swap_ints    — the pointer-param swap used by reverse
 */

#include <stdio.h>
#include <stdlib.h>

/* --- Helper: swap two ints via pointers (fill this in) --- */
void swap_ints(int *a, int *b)
{
    int temp = *a;  // FIX ME
    *a = *b;  // FIX ME
    *b = temp;
}

/* --- Function 1: print array using pointer arithmetic --- */
void array_print(int *arr, int len)
{
    printf("[");
    for (int i = 0; i < len; i++) {
        /* Use pointer arithmetic: *(arr + i) instead of arr[i] */
        printf("%d", *(arr + i));  // FIX ME
        if (i < len - 1) {
            printf(", ");
        }
    }
    printf("]");
}

/* --- Function 2: sum array using pointer arithmetic --- */
int array_sum(int *arr, int len)
{
    int total = 0;
    for (int i = 0; i < len; i++) {
        /* Use pointer arithmetic to read each element */
        total += *(arr + i);  // FIX ME
    }
    return total;
}

/* --- Function 3: reverse array in-place using swap_ints --- */
void array_reverse(int *arr, int len)
{
    for (int i = 0; i < len / 2; i++) {
        /* Swap arr[i] with arr[len - 1 - i] using swap_ints */
        swap_ints(&arr[i], &arr[len - 1 - i]);  // FIX ME  // FIX ME
    }
}

int main(void)
{
    int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    int len       = sizeof(numbers) / sizeof(numbers[0]);

    printf("Original array:  ");
    array_print(numbers, len);
    printf("\n");

    int total = array_sum(numbers, len);
    printf("Sum (via pointer arithmetic): %d  (expected: 36)\n", total);

    array_reverse(numbers, len);
    printf("Reversed array:  ");
    array_print(numbers, len);
    printf("\n");

    /* Reverse again to put it back */
    array_reverse(numbers, len);
    printf("Back to original: ");
    array_print(numbers, len);
    printf("\n");

    return EXIT_SUCCESS;
}

/*
 * Expected output:
 *   Original array:  [1, 2, 3, 4, 5, 6, 7, 8]
 *   Sum (via pointer arithmetic): 36  (expected: 36)
 *   Reversed array:  [8, 7, 6, 5, 4, 3, 2, 1]
 *   Back to original: [1, 2, 3, 4, 5, 6, 7, 8]
 */
