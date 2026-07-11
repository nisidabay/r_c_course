/*
 * Exercise 03: Strings become conscious with String_Slice — SOLUTION
 *
 * Concept: A String_Slice bundles a char* with its length. Now functions
 *          KNOW the length without scanning for '\0'. strlen is called
 *          ONCE during construction, never again.
 *
 * Note: Exercises 03+ use size_t (from <stddef.h>).
 *
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_03_string_slice.c -o ex_03_string_slice
 */

#include <stddef.h>   // size_t is an unsigned integer type from <stddef.h>, used for sizes and indices
#include <stdio.h>
#include <string.h>

/* Define the String_Slice struct: a char* data and a size_t len */
typedef struct {
    char   *data;
    size_t  len;
} String_Slice;

/* Build a slice from a null-terminated C string.
 * strlen is called ONCE during construction, never again. */
String_Slice slice_from_cstring(char *cstring) {
    return (String_Slice){
        .data = cstring,
        .len  = strlen(cstring),
    };
}

int main(void) {
    char *greeting = "hello world";

    /* Old way: char* + strlen every time */
    printf("Old way:  \"%s\"  strlen = %zu  (O(n) every call)\n",
           greeting, strlen(greeting));

    /* New way: String_Slice bundles data + length */
    String_Slice s = slice_from_cstring(greeting);

    printf("New way:  data = %p  len = %zu  (O(1) — length is stored)\n",
           (void *)s.data, s.len);

    /* Print each character using known length — no '\0' needed */
    printf("Characters by known length:  ");
    for (size_t i = 0; i < s.len; ++i) {
        putchar(s.data[i]);
    }
    putchar('\n');

    printf("\nEach slice knows its length instantly — no scanning required.\n");
    printf("The char* still points to the original memory. Nothing was copied.\n");

    return 0;
}
