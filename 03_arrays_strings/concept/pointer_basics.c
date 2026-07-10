/*
 * How do pointers relate to arrays?
 *
 * In most contexts, an array name "decays" to a pointer to
 * its first element.  Pointer arithmetic then lets you walk
 * through the array.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const int numbers[] = {10, 20, 30, 40, 50};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);

    /* The array name decays to &numbers[0] */
    const int *ptr = numbers;
    printf("numbers[0]    = %d\n", numbers[0]);
    printf("*ptr          = %d  (same value)\n", *ptr);

    /* Pointer arithmetic: ptr + n gives address of element n */
    printf("\nWalking with pointer arithmetic:\n");
    for (size_t i = 0; i < count; ++i) {
        printf("  *(ptr + %zu) = %d   (address %p)\n",
               i, *(ptr + i), (void *)(ptr + i));
    }

    /* The & operator gets the address of a specific element */
    const int *third = &numbers[2];
    printf("\n&numbers[2]      = %p\n", (void *)third);
    printf("*(&numbers[2])   = %d\n", *third);

    /* Array indexing is syntactic sugar for pointer arithmetic */
    printf("\nnumbers[3]       = %d\n", numbers[3]);
    printf("*(numbers + 3)   = %d\n", *(numbers + 3));

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * The expression numbers[i] is defined as *(numbers + i).
 * This means i[numbers] also compiles (because addition is
 * commutative), but never write that in real code.  When you
 * pass an array to a function, what the function receives is
 * a pointer -- sizeof inside the function gives the pointer
 * size, not the array size.  Always pass the length alongside.
 * ============================================================
 */


// 💡 Thinking in C:
// A pointer holds an address. The-and-x gives the address, star-p follows it. They are different C expressions.
