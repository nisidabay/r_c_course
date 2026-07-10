/*
 * 05_growable_array.c
 * Group 07 — Dynamic Memory
 * Concept: building a simple dynamic int array
 *
 * We wrap a heap-allocated buffer in a struct that tracks
 * length (how many elements are in use) and capacity (how
 * many slots are allocated).  append() grows the array
 * via realloc when needed, doubling the capacity to avoid
 * O(n) reallocation on every insertion.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int   *data;      /* heap-allocated buffer */
    size_t len;       /* elements currently in use */
    size_t cap;       /* allocated slot count */
} DynArr;

/* Append one integer to the dynamic array.  Doubles capacity when full. */
int dynarr_append(DynArr *arr, int value)
{
    if (arr->len == arr->cap) {
        size_t new_cap = arr->cap == 0 ? 4 : arr->cap * 2;
        int *temp = realloc(arr->data, new_cap * sizeof(int));
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
    free(arr->data);
    arr->data = NULL;
    arr->len  = 0;
    arr->cap  = 0;
}

int main(void)
{
    DynArr items = { NULL, 0, 0 };
    int values[] = { 10, 20, 30, 40, 50, 60, 70 };
    size_t n = sizeof(values) / sizeof(values[0]);

    /* Append each value — array grows automatically */
    for (size_t i = 0; i < n; i++) {
        if (dynarr_append(&items, values[i]) != 0) {
            dynarr_free(&items);
            return 1;
        }
    }

    printf("Dynamic array: len=%zu  cap=%zu\n", items.len, items.cap);
    for (size_t i = 0; i < items.len; i++) {
        printf("  items[%zu] = %d\n", i, items.data[i]);
    }

    printf("\nAppended %zu elements — capacity grew to %zu.\n", n, items.cap);
    printf("The array could keep growing; no fixed limit.\n");

    dynarr_free(&items);
    return 0;
}
/*
 * Thinking in C:
 * A dynamic array is just a pointer + length + capacity in a struct.
 * Doubling capacity on each growth gives amortised O(1) append.
 * The struct must be initialised to {NULL, 0, 0} so first realloc
 * acts as malloc(NULL is safe for realloc).
 * Always free everything — even on error paths.
 */
