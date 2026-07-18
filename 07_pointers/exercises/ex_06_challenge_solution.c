/*
 * ex_06_challenge.c — SOLUTION
 * Group 06 — Pointers 101
 * Challenge: pointer params + arrays + pointer arithmetic
 */

#include <stdio.h>

/* --- Helper: swap two ints via pointers --- */
void swap_ints(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* --- Function 1: print array using pointer arithmetic --- */
void array_print(int *arr, int len)
{
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%d", *(arr + i));
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
        total += *(arr + i);
    }
    return total;
}

/* --- Function 3: reverse array in-place using swap_ints --- */
void array_reverse(int *arr, int len)
{
    for (int i = 0; i < len / 2; i++) {
        swap_ints(&arr[i], &arr[len - 1 - i]);
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

    return 0;
}
