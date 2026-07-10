/*
 * Exercise 01: Heap vs Stack — SOLUTION
 *
 * Concept: Stack arrays are fixed-size; heap allocations can grow.
 *
 * Safe C Standard: int main(void), no scanf/atoi.
 */

#include <stdio.h>
#include <stdlib.h>

#define STACK_SZ 5

int main(void)
{
    /* Stack array — size fixed at compile time */
    int stack_arr[STACK_SZ];
    printf("Stack array size: %zu elements (fixed at compile time)\n",
           sizeof(stack_arr) / sizeof(stack_arr[0]));

    /* Heap allocation — size determined at runtime */
    size_t heap_sz = 10;
    int *heap_arr = malloc(heap_sz * sizeof(int));
    if (heap_arr == NULL) {
        printf("ERROR: malloc failed\n");
        return 1;
    }

    printf("Heap array size: %zu elements (set at runtime)\n", heap_sz);
    printf("Heap arrays can be much larger than stack arrays.\n");
    printf("Stack arrays cannot be resized; heap arrays can (via realloc).\n");

    /* Fill heap array */
    for (size_t i = 0; i < heap_sz; i++) {
        heap_arr[i] = (int)i;
    }
    printf("heap_arr[0] = %d, heap_arr[9] = %d\n",
           heap_arr[0], heap_arr[9]);

    free(heap_arr);
    return 0;
}
