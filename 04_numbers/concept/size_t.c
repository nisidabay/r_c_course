/*
 * How do I use size_t correctly?
 *
 * size_t is the unsigned integer type returned by sizeof
 * and used for array indices and object sizes.  It matches
 * the address space width.  Use %zu to printf it.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* sizeof returns size_t */
    const size_t int_size = sizeof(int);
    const size_t double_size = sizeof(double);

    printf("sizeof(int)    = %zu bytes\n", int_size);
    printf("sizeof(double) = %zu bytes\n", double_size);

    /* size_t for array indices -- avoids signed/unsigned warnings */
    const int data[] = {10, 20, 30, 40, 50};
    const size_t count = sizeof(data) / sizeof(data[0]);

    printf("\nArray has %zu elements:\n", count);
    for (size_t i = 0; i < count; ++i) {
        printf("  data[%zu] = %d\n", i, data[i]);
    }

    /* size_t can hold the maximum object size */
    printf("\nMaximum value of size_t on this platform: %zu\n",
           (size_t)-1);

    /* Printing size_t with %zu */
    const size_t n = 42;
    printf("size_t value:  %zu\n", n);
    printf("size_t as hex: 0x%zx\n", n);

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * Never use int for array indices or object sizes.  int may
 * be too small on 64-bit systems, and mixing signed/unsigned
 * types triggers compiler warnings.  size_t is unsigned and
 * wide enough for any object in memory.  Always use %zu for
 * printf, never %lu or %u -- those are not portable.
 * ============================================================
 */


// 💡 Thinking in C:
// size_t is unsigned and matches your platform word size. Use it for lengths, array indices, and counts.
