/*
 * Mini-Challenge 07: Growable Integer Array
 *
 * Implement a growable integer array with push, pop, and get operations.
 * Use the struct: struct { int *data; size_t len; size_t cap; }
 * All operations must be safe — NULL-check every allocation.
 *
 * Your task:
 *   1. Implement dynarr_create()  — allocate initial capacity
 *   2. Implement dynarr_push()    — append a value, grow via realloc with temp ptr
 *   3. Implement dynarr_pop()     — remove and return the last value
 *   4. Implement dynarr_get()     — return value at index (bounds-checked)
 *   5. Implement dynarr_free()    — clean up all memory
 *   6. Implement main() that demonstrates all operations
 *
 * Rules:
 *   - No strcpy/strcat/sprintf/scanf/atoi/atof
 *   - snprintf for string building if needed
 *   - All malloc/calloc/realloc NULL-checked
 *   - int main(void)
 *   - Compiles with -std=c11
 *
 * Expected output (exact):
 *   Push: 10 20 30 40 50
 *   Pop: got 50
 *   Get[0]=10  Get[1]=20  Get[2]=30  Get[3]=40
 *   After push 60: 10 20 30 40 60
 *   Pop error: array is empty
 *   Final array freed.
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
    (void)arr;
    (void)initial_cap;
    return 1;  // FIX ME
}

/*
 * Push a value to the end of the array.
 * If full, double capacity using realloc with a TEMP pointer.
 * Returns 0 on success, 1 on allocation failure.
 */
int dynarr_push(DynIntArr *arr, int value)
{
    (void)arr;
    (void)value;
    return 1;  // FIX ME
}

/*
 * Pop the last value from the array.
 * Stores the value at *out.
 * Returns 0 on success, 1 if the array is empty.
 */
int dynarr_pop(DynIntArr *arr, int *out)
{
    (void)arr;
    (void)out;
    return 1;  // FIX ME
}

/*
 * Get the value at index i (bounds-checked).
 * Stores the value at *out.
 * Returns 0 on success, 1 if index is out of bounds.
 */
int dynarr_get(DynIntArr *arr, size_t i, int *out)
{
    (void)arr;
    (void)i;
    (void)out;
    return 1;  // FIX ME
}

/* Free all memory owned by the array and reset fields. */
void dynarr_free(DynIntArr *arr)
{
    (void)arr;  // FIX ME
}

int main(void)
{
    DynIntArr arr;
    int val;
    int ret;

    /* Create with initial capacity 4 */
    if (dynarr_create(&arr, 4) != 0) {
        printf("ERROR: dynarr_create failed\n");
        return 1;
    }

    /* Push 10, 20, 30, 40, 50 (triggers growth) */
    printf("Push:");
    for (int i = 1; i <= 5; i++) {
        if (dynarr_push(&arr, i * 10) != 0) {
            printf("\nERROR: dynarr_push failed\n");
            dynarr_free(&arr);
            return 1;
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
        return 1;
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

    return 0;
}
