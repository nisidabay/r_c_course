/*
 * 11_double_pointer.c — int **p (pointer to pointer)
 * Group 06 - Pointers 101
 *
 * A pointer can point to another pointer.  int **p_ptr_x stores
 * the address of int *ptr_x, which stores the address of int x.
 *
 *   x = 42           value
 *   ptr_x = &x       pointer holds address of x
 *   p_ptr_x = &ptr_x double-pointer holds address of ptr_x
 *
 *   *ptr_x   == x          == 42
 *   **p_ptr_x == *ptr_x    == 42
 *
 * Double pointers are used for modifying pointer parameters,
 * arrays of strings (char **argv), and dynamic 2D allocations.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int x = 0;
    int *ptr_x   = &x;
    int **p_ptr_x = &ptr_x;

    /* --- Get input using the standard fgets+strtol pattern --- */
    char buf[64];
    printf("Enter an integer: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    buf[strcspn(buf, "\n")] = '\0';

    char *endptr;
    errno = 0;
    long val = strtol(buf, &endptr, 10);
    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    if (endptr == buf || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Number out of range for int\n");
        return EXIT_FAILURE;
    }
    x = (int)val;

    /* --- Double pointer indirection --- */
    printf("\n=== Double pointer walkthrough ===\n");
    printf("  x           = %d\n", x);
    printf("  &x          = %p\n", (void *)&x);
    printf("  ptr_x       = %p\n", (void *)ptr_x);
    printf("  *ptr_x      = %d\n", *ptr_x);
    printf("  &ptr_x      = %p\n", (void *)&ptr_x);
    printf("  p_ptr_x     = %p\n", (void *)p_ptr_x);
    printf("  *p_ptr_x    = %p\n", (void *)*p_ptr_x);
    printf("  **p_ptr_x   = %d\n", **p_ptr_x);

    printf("\n  x == *ptr_x == **p_ptr_x  ->  ");
    if (x == *ptr_x && *ptr_x == **p_ptr_x) {
        puts("all three are equal ✓");
    } else {
        puts("MISMATCH");
    }

    return EXIT_SUCCESS;
}

// Thinking in C:
// int **p is a pointer to a pointer to int.  Each * peels off
// one level of indirection.  Double pointers are fundamental for:
//   - Modifying a pointer parameter (e.g., realloc inside a function)
//   - Arrays of strings: char **argv
//   - Dynamic 2D arrays allocated row by row
// Read declarations right-to-left: p_ptr_x is a pointer to a
// pointer to int.
