/*
 * How do I declare and use arrays?
 *
 * An array is a contiguous block of elements of the same type.
 * sizeof gives the total byte count; divide by element size
 * to get the number of elements.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Declare and initialise in one shot */
    const int primes[] = {2, 3, 5, 7, 11};

    /* sizeof(array) / sizeof(element) gives element count */
    const size_t count = sizeof(primes) / sizeof(primes[0]);
    printf("Array has %zu elements.\n", count);

    for (size_t i = 0; i < count; ++i) {
        printf("  primes[%zu] = %d\n", i, primes[i]);
    }

    /* Partial initialisation -- missing elements are zero */
    int zeroed[10] = {1, 2, 3};
    printf("\nzeroed[0] = %d\n", zeroed[0]);
    printf("zeroed[3] = %d (implicitly zero)\n", zeroed[3]);
    printf("zeroed[9] = %d (implicitly zero)\n", zeroed[9]);

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * Arrays are zero-indexed: the first element is at index 0.
 * There is no bounds checking at runtime -- accessing
 * primes[100] compiles fine but produces undefined behaviour.
 * The sizeof / sizeof(primes[0]) trick only works on actual
 * arrays, not on pointers.  Once an array "decays" to a
 * pointer (e.g. when passed to a function), you must pass
 * the size separately.
 * ============================================================
 */


// 💡 Thinking in C:
// Arrays are contiguous memory. Index from 0. C does NOT check bounds — you must.
