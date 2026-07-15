/*
 * Mini-Challenge 07: Growable Integer Array — SOLUTION
 *
 * Implement a growable integer array with push, pop, and get operations.
 *
 * Rules:
 *   - No strcpy/strcat/sprintf/scanf/atoi/atof
 *   - All malloc/calloc/realloc NULL-checked
 *   - int main(void), compile with -std=c11
 */

#include <stdio.h>
#include <stdlib.h>

/* --- Define the DynIntArr struct --- */
typedef struct {
    int *data;    /* heap-allocated buffer */
    size_t len;   /* elements currently stored */
    size_t cap;   /* allocated capacity */
} DynIntArr;

/*
 * Create a new dynamic array with the given initial capacity.
 * Returns 0 on success, 1 on allocation failure.
 */
int dynarr_create(DynIntArr *arr, size_t initial_cap)
{
    arr->data = malloc(initial_cap * sizeof(int));
    if (arr->data == NULL) {
        return 1;
    }
    arr->len = 0;
    arr->cap = initial_cap;
    return 0;
}

/*
 * Push a value to the end of the array.
 * If full, double capacity using realloc with a TEMP pointer.
 * Returns 0 on success, 1 on allocation failure.
 */
int dynarr_push(DynIntArr *arr, int value)
{
    if (arr->len == arr->cap) {
        size_t new_cap = arr->cap == 0 ? 4 : arr->cap * 2;
        int *temp = realloc(arr->data, new_cap * sizeof(int));
        if (temp == NULL) {
            return 1;
        }
        arr->data = temp;
        arr->cap = new_cap;
    }
    arr->data[arr->len] = value;
    arr->len++;
    return 0;
}

/*
 * Pop the last value from the array.
 * Stores the value at *out.
 * Returns 0 on success, 1 if the array is empty.
 */
int dynarr_pop(DynIntArr *arr, int *out)
{
    if (arr->len == 0) {
        return 1;
    }
    arr->len--;
    *out = arr->data[arr->len];
    return 0;
}

/*
 * Get the value at index i (bounds-checked).
 * Stores the value at *out.
 * Returns 0 on success, 1 if index is out of bounds.
 */
int dynarr_get(DynIntArr *arr, size_t i, int *out)
{
    if (i >= arr->len) {
        return 1;
    }
    *out = arr->data[i];
    return 0;
}

/* Free all memory owned by the array and reset fields. */
void dynarr_free(DynIntArr *arr)
{
    free(arr->data);
    arr->data = NULL;
    arr->len = 0;
    arr->cap = 0;
}

int main(void)
{
    DynIntArr arr;
    int val;
    int ret;

    /* Create with initial capacity 4 */
    if (dynarr_create(&arr, 4) != 0) {
        printf("ERROR: dynarr_create failed\n");
        return EXIT_FAILURE;
    }

    /* Push 10, 20, 30, 40, 50 (triggers growth) */
    printf("Push:");
    for (int i = 1; i <= 5; i++) {
        if (dynarr_push(&arr, i * 10) != 0) {
            printf("\nERROR: dynarr_push failed\n");
            dynarr_free(&arr);
            return EXIT_FAILURE;
        }
        printf(" %d", i * 10);
    }
    printf("\n");

    /* Pop once */
    ret = dynarr_pop(&arr, &val);
    if (ret == 0) {
        printf("Pop: got %d\n", val);
    } else {
        printf("Pop error: array is empty\n");
    }

    /* Get elements at indices 0-3 */
    printf("Get[0]=%d  Get[1]=%d  Get[2]=%d  Get[3]=%d\n",
           (dynarr_get(&arr, 0, &val) == 0 ? (val) : 0),
           (dynarr_get(&arr, 1, &val) == 0 ? (val) : 0),
           (dynarr_get(&arr, 2, &val) == 0 ? (val) : 0),
           (dynarr_get(&arr, 3, &val) == 0 ? (val) : 0));

    /* Push 60 */
    if (dynarr_push(&arr, 60) != 0) {
            printf("ERROR: dynarr_push failed\n");
            dynarr_free(&arr);
            return EXIT_FAILURE;
    }

    printf("After push 60:");
    for (size_t i = 0; i < arr.len; i++) {
        printf(" %d", arr.data[i]);
    }
    printf("\n");

    /* Pop until empty — should get one "empty" error */
    while (dynarr_pop(&arr, &val) == 0) {
        /* drain */
    }
    printf("Pop error: array is empty\n");

    /* Clean up */
    dynarr_free(&arr);
    printf("Final array freed.\n");

    return EXIT_SUCCESS;
}
