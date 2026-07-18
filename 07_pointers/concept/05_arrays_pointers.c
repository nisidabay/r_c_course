/*
 * 05_arrays_pointers.c — array decay, pointer arithmetic, a[i] == *(a+i)
 *
 * In C, an array name "decays" to a pointer to its first element.
 * This means arr IS &arr[0]. From there, pointer arithmetic applies:
 * p+1 advances by sizeof(element), so *(arr + i) == arr[i].
 *
 * The bracket notation arr[i] is SYNTAX SUGAR for *(arr + i).
 * Understanding this equivalence is the key to mastering C arrays.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int arr[] = {10, 20, 30, 40, 50};
    int len   = sizeof(arr) / sizeof(arr[0]);

    /* -- Array decay: arr is the same as &arr[0] -- */
    printf("arr                   = %p\n", (void *)arr);
    printf("&arr[0]               = %p\n", (void *)&arr[0]);
    printf("arr == &arr[0]?        %s\n\n",
           arr == &arr[0] ? "YES — array decays to &arr[0]" : "NO");

    /* -- Pointer arithmetic: p+1 advances by sizeof(int) -- */
    int *p = arr;   /* p points to arr[0] */
    printf("p           = %p\n", (void *)p);
    printf("p + 1       = %p\n", (void *)(p + 1));
    printf("p + 2       = %p\n", (void *)(p + 2));
    printf("sizeof(int) = %zu bytes\n\n", sizeof(int));

    /* -- a[i] is syntactic sugar for *(a + i) -- */
    printf("=== arr[i] == *(arr + i) ===\n");
    for (int i = 0; i < len; i++) {
        printf("arr[%d] = %d    *(arr + %d) = %d    %s\n",
               i, arr[i],
               i, *(arr + i),
               arr[i] == *(arr + i) ? "✓ equal" : "✗ MISMATCH");
    }

    /* -- Writing via pointer arithmetic -- */
    printf("\n=== Writing through pointer arithmetic ===\n");
    *(arr + 2) = 300;   /* same as arr[2] = 300 */
    printf("After *(arr + 2) = 300:\n");
    for (int i = 0; i < len; i++) {
        printf("  arr[%d] = %d\n", i, arr[i]);
    }

    return EXIT_SUCCESS;
}

/*
 * Thinking in C:
 *   arr is &arr[0] — the array name decays to a pointer to the first element.
 *   p + 1 advances by sizeof(type), not by 1 byte.
 *   arr[i] is exactly *(arr + i) — one is bracket sugar for the other.
 *   Pointer arithmetic and array indexing are two faces of the same coin.
 */
