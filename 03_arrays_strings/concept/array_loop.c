/*
 * How do I iterate over arrays?
 *
 * The two main patterns are index-based and pointer-based
 * traversal.  Sentinel values mark the end when the length
 * is not known ahead of time.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Index-based iteration */
    const int data[] = {5, 10, 15, 20, 25};
    const size_t count = sizeof(data) / sizeof(data[0]);

    printf("Index-based loop:\n");
    for (size_t i = 0; i < count; ++i) {
        printf("  data[%zu] = %d\n", i, data[i]);
    }

    /* Pointer-based traversal */
    printf("\nPointer traversal:\n");
    const int *start = data;
    const int *end = data + count;
    for (const int *p = start; p < end; ++p) {
        printf("  %d\n", *p);
    }

    /* Sentinel value -- -1 marks the end */
    const int sentinel_data[] = {10, 20, 30, 40, -1};

    printf("\nSentinel-terminated loop:\n");
    for (size_t i = 0; sentinel_data[i] != -1; ++i) {
        printf("  sentinel_data[%zu] = %d\n", i, sentinel_data[i]);
    }

    /* Also works with pointer traversal */
    printf("\nPointer traversal with sentinel:\n");
    for (const int *p = sentinel_data; *p != -1; ++p) {
        printf("  %d\n", *p);
    }

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * Index-based loops are straightforward and familiar.
 * Pointer-based loops are often faster (the compiler can
 * optimise the address arithmetic) and are idiomatic in
 * C library code.  Sentinels are common for variable-length
 * sequences that don't carry an explicit count -- just make
 * sure the sentinel value cannot appear as real data.
 * ============================================================
 */


// 💡 Thinking in C:
// arr[i] is syntactic sugar for star(arr + i). The compiler generates the same code.
