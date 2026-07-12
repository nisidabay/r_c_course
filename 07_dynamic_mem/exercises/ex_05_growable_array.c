/*
 * Exercise 05: Growable Array
 *
 * Concept: Wrapping a heap buffer in a struct with len/cap.
 * Use realloc with temp pointer to grow when full.
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * The program should:
 *   1. Define a DynArr struct with data, len, cap fields
 *   2. Implement dynarr_append — grows via realloc when len == cap
 *   3. Implement dynarr_free
 *   4. Append 5 values and print them
 *
 * Rules: No strcpy/strcat/sprintf/scanf/atoi.
 * All malloc NULL-checked. int main(void).
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;           // FIX ME
    size_t len;          // FIX ME
    size_t cap;          // FIX ME
} DynArr;

/* Append one integer. Doubles capacity when full. */
int dynarr_append(DynArr *arr, int value)
{
    if (arr->len == arr->cap) {
        size_t new_cap = arr->cap == 0 ? 4 : arr->cap * 2;
        int *temp = realloc(arr->data, new_cap * sizeof(int));  // FIX ME
        if (temp == NULL) {
            perror("dynarr_append realloc");
            return 1;
        }
        arr->data = temp;
        arr->cap  = new_cap;
    }
    arr->data[arr->len] = value;
    arr->len++;
    return 0;
}

/* Free all owned memory */
void dynarr_free(DynArr *arr)
{
    free(arr->data);  // FIX ME
    arr->data = NULL;
    arr->len  = 0;
    arr->cap  = 0;
}

int main(void)
{
    DynArr arr = { NULL, 0, 0 };
    int vals[] = { 5, 10, 15, 20, 25 };
    size_t n = sizeof(vals) / sizeof(vals[0]);

    for (size_t i = 0; i < n; i++) {
        if (dynarr_append(&arr, vals[i]) != 0) {  // FIX ME
            dynarr_free(&arr);
            return EXIT_FAILURE;
        }
    }

    printf("Dynamic array: len=%zu  cap=%zu\n", arr.len, arr.cap);
    for (size_t i = 0; i < arr.len; i++) {
        printf("  arr[%zu] = %d\n", i, arr.data[i]);
    }

    printf("\nAppended %zu elements — capacity grew to %zu.\n", n, arr.cap);
    printf("The array can keep growing with no fixed limit.\n");

    dynarr_free(&arr);  // FIX ME
    return EXIT_SUCCESS;
}
/*
 * Thinking in C:
 * A dynamic array is pointer + length + capacity in a struct.
 * Doubling capacity on growth gives amortised O(1) append.
 * Initialise struct to {NULL, 0, 0} so first realloc acts as malloc.
 * Always free everything, even on error paths.
 */
