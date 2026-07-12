/*
 * Exercise 03: Strings become conscious with String_Slice
 *
 * Concept: A String_Slice bundles a char* with its length. Now functions
 *          KNOW the length without scanning for '\0'. strlen is called
 *          ONCE during construction, never again.
 *
 * Fill in the blanks (marked BLANK) to complete the program.
 * You must fill in the String_Slice struct definition and the
 * slice_from_cstring function.
 *
 * Note: Exercises 03+ use size_t (from <stddef.h>).
 *
 * Safe C Standard: no strcpy/strcat/sprintf/scanf/atoi/atof.
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_03_string_slice.c -o ex_03_string_slice
 */

#include <stddef.h>   // size_t is an unsigned integer type from <stddef.h>, used for sizes and indices
#include <stdio.h>
#include <string.h>

/* Define the String_Slice struct: a char* data and a size_t len */
typedef struct {
    char   *data; // FIX ME
    size_t  len;  // FIX ME
} String_Slice;

/* Build a slice from a null-terminated C string.
 * strlen is called ONCE during construction, never again. */
String_Slice slice_from_cstring(char *cstring) {
    return (String_Slice){
        .data = cstring,         // FIX ME
        .len  = strlen(cstring), // FIX ME
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
