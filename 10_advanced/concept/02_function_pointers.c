/*
 * File:  02_function_pointers.c
 * Group: 10 — Paradigm Shift: Function Pointers
 *
 * Concept: Declaring, assigning, and calling through a function pointer
 *
 * Three distinct steps shown here:
 *   1. DECLARE —  int (*cmp)(int, int)
 *   2. ASSIGN  —  cmp = compare_asc;
 *   3. CALL    —  result = cmp(a, b);
 *
 * Shows:
 *   - Two comparison functions: ascending and descending
 *   - A function pointer variable that can switch between them at runtime
 *   - Dynamic memory (group 09) to build an array of scores
 *   - snprintf for safe string formatting
 *
 * Build:  gcc -std=c11 -Wall -Wextra -pedantic 02_function_pointers.c -o 02_function_pointers
 * Run:    ./02_function_pointers
 */

#include <stdio.h>
#include <stdlib.h>

/* ---------- two comparison functions with identical signatures ---------- */
int compare_asc(int a, int b)  { return (a > b) - (a < b); } /* -1, 0, or +1 */
int compare_desc(int a, int b) { return (b > a) - (b < a); }

/* ---------- bubble sort that accepts a comparator via function pointer ---------- */
void sort(int *arr, size_t n, int (*cmp)(int, int)) {
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            /* STEP 3 — CALL through the pointer */
            if (cmp(arr[i], arr[j]) > 0) {
                int tmp  = arr[i];
                arr[i]   = arr[j];
                arr[j]   = tmp;
            }
        }
    }
}

int main(void) {
    /* STEP 1 — DECLARE a function pointer: return_type (*name)(param_types) */
    int (*cmp)(int, int) = NULL;

    /* dynamic array of scores (group 09: dynamic memory) */
    size_t n = 6;
    int   *scores = malloc(n * sizeof(int));
    if (!scores) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    scores[0] = 85; scores[1] = 92; scores[2] = 78;
    scores[3] = 95; scores[4] = 88; scores[5] = 73;

    char buf[128];

    /* --- ascending sort --- */
    /* STEP 2 — ASSIGN the function's address to the pointer */
    cmp = compare_asc;
    sort(scores, n, cmp);

    snprintf(buf, sizeof buf, "Ascending:  ");
    for (size_t i = 0; i < n; i++) {
        char tmp[16];
        snprintf(tmp, sizeof tmp, "%d ", scores[i]);
        /* string concatenation via snprintf offset (group 07) */
        /* find the null terminator and continue building */
        size_t off = 0;
        while (buf[off]) off++;
        snprintf(buf + off, sizeof buf - off, "%s", tmp);
    }
    printf("%s\n", buf);

    /* --- descending sort --- */
    cmp = compare_desc;
    sort(scores, n, cmp);

    snprintf(buf, sizeof buf, "Descending: ");
    for (size_t i = 0; i < n; i++) {
        size_t off = 0;
        while (buf[off]) off++;
        char tmp[16];
        snprintf(tmp, sizeof tmp, "%d ", scores[i]);
        snprintf(buf + off, sizeof buf - off, "%s", tmp);
    }
    printf("%s\n", buf);

    free(scores);
    return 0;
}

/*
 * Thinking in C — Group 10
 *
 * A function pointer is just a variable that holds a code address.
 * The syntax int (*cmp)(int, int) reads: "cmp is a pointer to a function
 * that takes two ints and returns int."  Declare it, assign it, call it —
 * three distinct acts that let you swap behaviour at runtime without
 * touching a single if/else.  This is the foundation of callbacks.
 */
