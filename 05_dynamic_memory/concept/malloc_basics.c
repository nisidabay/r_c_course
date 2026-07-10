/*
 * How do I allocate memory with malloc?
 *
 * This file demonstrates the basic pattern for dynamic memory allocation:
 * malloc with sizeof, NULL-check, use, and free.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Allocate an array of 10 ints on the heap */
    int *arr = (int *)malloc(10 * sizeof(int));
    if (arr == NULL) {
        perror("malloc failed");
        return EXIT_FAILURE;
    }

    /* Use the memory */
    for (size_t i = 0; i < 10; i++) {
        arr[i] = (int)(i * i);
    }

    for (size_t i = 0; i < 10; i++) {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    /* Release the memory back to the OS */
    free(arr);

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// malloc returns NULL on failure. Always check the return value before using the pointer.
