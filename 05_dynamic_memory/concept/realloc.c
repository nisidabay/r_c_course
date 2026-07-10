/*
 * How do I resize memory with realloc?
 *
 * This file demonstrates growing and shrinking a heap allocation
 * with realloc, and handling its NULL return safely.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Start with an array of 4 ints */
    int *arr = (int *)malloc(4 * sizeof(int));
    if (arr == NULL) {
        perror("initial malloc failed");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < 4; i++) {
        arr[i] = (int)(i + 1);
    }

    /* Grow the array to 8 ints */
    int *tmp = (int *)realloc(arr, 8 * sizeof(int));
    if (tmp == NULL) {
        perror("realloc (grow) failed");
        free(arr);
        return EXIT_FAILURE;
    }
    arr = tmp;

    /* Fill new elements */
    for (size_t i = 4; i < 8; i++) {
        arr[i] = (int)(i + 1);
    }

    for (size_t i = 0; i < 8; i++) {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    /* Shrink the array back to 4 ints */
    tmp = (int *)realloc(arr, 4 * sizeof(int));
    if (tmp == NULL) {
        /* On shrink failure the original block is still valid */
        perror("realloc (shrink) failed");
        free(arr);
        return EXIT_FAILURE;
    }
    arr = tmp;

    printf("\nAfter shrink:\n");
    for (size_t i = 0; i < 4; i++) {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    free(arr);
    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// realloc can grow or shrink memory. It returns a new pointer — update your variable.
