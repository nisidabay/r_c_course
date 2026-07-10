/*
 * How do I grow an array dynamically?
 *
 * This file demonstrates a dynamic array that doubles its capacity
 * using realloc each time it fills up.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t capacity = 4;
    size_t count = 0;

    int *arr = (int *)malloc(capacity * sizeof(int));
    if (arr == NULL) {
        perror("initial malloc failed");
        return EXIT_FAILURE;
    }

    /* Add numbers 1..20, doubling capacity as needed */
    for (int value = 1; value <= 20; value++) {
        if (count == capacity) {
            /* Double the capacity */
            size_t new_cap = capacity * 2;
            int *tmp = (int *)realloc(arr, new_cap * sizeof(int));
            if (tmp == NULL) {
                perror("realloc failed during growth");
                free(arr);
                return EXIT_FAILURE;
            }
            arr = tmp;
            capacity = new_cap;
            printf("Resized to capacity %zu\n", capacity);
        }

        arr[count] = value;
        count++;
    }

    printf("\nStored %zu elements:\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');

    free(arr);
    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// Dynamic arrays grow by doubling capacity. realloc handles the copy when possible.
