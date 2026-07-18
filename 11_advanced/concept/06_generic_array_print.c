/*
 * 06_generic_array_print.c — _Generic + const void* with enum dispatch
 * Group 10 - Advanced
 *
 * Combine C11's _Generic with a const void* + enum dispatch pattern
 * to build a single function that prints arrays of different types.
 *
 * _Generic selects code at compile-time based on the type of the
 * controlling expression (zero runtime cost).  const void* lets us
 * accept arrays of any type without knowing the element size.
 * An enum DataType tells the runtime which cast to use.
 *
 * This is a stepping-stone to truly generic data structures.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- enum for explicit type flags ---- */
typedef enum { TYPE_INT, TYPE_CHAR } DataType;

/* ---- generic array printer using const void * + enum ---- */
void print_array(const void *arr, size_t n, DataType type)
{
    if (arr == NULL) {
        return;
    }

    if (type == TYPE_INT) {
        const int *int_arr = (const int *)arr;
        for (size_t i = 0; i < n; i++) {
            printf("%d ", int_arr[i]);
        }
    } else if (type == TYPE_CHAR) {
        const char *char_arr = (const char *)arr;
        for (size_t i = 0; i < n; i++) {
            printf("%c ", char_arr[i]);
        }
    }

    printf("\n");
}

int main(void)
{
    /* Integer array */
    int data[] = {1, 2, 3, 4, 5};
    size_t n_int = sizeof(data) / sizeof(data[0]);

    printf("Integer array:  ");
    print_array(data, n_int, TYPE_INT);

    /* Character array (subtract 1 to skip null terminator) */
    char greeting[] = "HELLO";
    size_t n_char = sizeof(greeting) / sizeof(greeting[0]) - 1;

    printf("Character array: ");
    print_array(greeting, n_char, TYPE_CHAR);

    return EXIT_SUCCESS;
}

// Thinking in C:
// const void * is C's universal pointer — it can point to anything
// but cannot be dereferenced without a cast.  An enum flag + switch
// on type is the closest C gets to runtime polymorphism without
// function pointers or _Generic.  _Generic does it at compile-time;
// enum dispatch does it at runtime.  Both are valid approaches for
// different needs.
