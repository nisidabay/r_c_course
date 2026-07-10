/*
 * How do I use C's basic data types?
 *
 * C provides a small set of fundamental types from which all
 * others are composed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    const int      i   = -100;
    const char     c   = 'A';
    const float    f   = 3.14159265f;
    const double   d   = 2.718281828459045;
    const _Bool    b1  = 1;
    const bool     b2  = true;   /* via <stdbool.h> */

    printf("int:     %d\n",    i);
    printf("char:    '%c' (ASCII %d)\n", c, (int)c);
    printf("float:   %.6f\n",  f);
    printf("double:  %.15f\n", d);
    printf("_Bool:   %d  %d\n", b1, b2);

    printf("\n--- sizeof (in bytes) ---\n");
    printf("char     : %zu\n", sizeof(char));
    printf("short    : %zu\n", sizeof(short));
    printf("int      : %zu\n", sizeof(int));
    printf("long     : %zu\n", sizeof(long));
    printf("float    : %zu\n", sizeof(float));
    printf("double   : %zu\n", sizeof(double));
    printf("_Bool    : %zu\n", sizeof(_Bool));
    printf("size_t   : %zu\n", sizeof(size_t));

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * Type sizes are platform-dependent.  sizeof gives you the true
 * width at compile time.  For integer types, <stdint.h> provides
 * fixed-width aliases (int32_t, uint64_t, ...) when you need
 * exact sizes.  Use size_t for array indices and object sizes --
 * it matches the address space width.
 * ============================================================
 */

// 💡 Thinking in C:
// int for integers, double for floats, char for single characters. size_t for sizes.
