/*
 * 03_string_slice.c — Strings become conscious with String_Slice
 *
 * Tony Banters' "Strings Aren't Real" — Day 3
 *
 * KEY INSIGHT: A String_Slice bundles a char* with its length.
 * Now functions KNOW the length without scanning for '\0'.
 * The data pointer may point into any memory — no copying.
 *
 * gcc -std=c11 -Wall -Wextra -pedantic 03_string_slice.c -o 03_string_slice
 */

#include <stddef.h>   // size_t is an unsigned integer type from <stddef.h>, used for sizes and indices
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char   *data;   /* pointer to the first character */
    size_t  len;    /* number of characters — known up front */
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

    /* Print each character with known length — no '\0' needed */
    printf("Characters by known length:  ");
    for (size_t i = 0; i < s.len; ++i) {
        putchar(s.data[i]);
    }
    putchar('\n');

    /* Multiple slices, different data pointers */
    char *name = "C programming";
    char *path = "/usr/local/bin";

    String_Slice s1 = slice_from_cstring(greeting);
    String_Slice s2 = slice_from_cstring(name);
    String_Slice s3 = slice_from_cstring(path);

    printf("\nSlice 1: data = %p  len = %zu  \"%s\"\n",
           (void *)s1.data, s1.len, s1.data);
    printf("Slice 2: data = %p  len = %zu  \"%s\"\n",
           (void *)s2.data, s2.len, s2.data);
    printf("Slice 3: data = %p  len = %zu  \"%s\"\n",
           (void *)s3.data, s3.len, s3.data);

    printf("\nEach slice knows its length instantly — no scanning required.\n");
    printf("The char* still points to the original memory. Nothing was copied.\n");

    return EXIT_SUCCESS;
}

// Thinking in C:
// String_Slice is C's way of making a string type: data pointer + known length.
// strlen is called exactly once (at construction), not every time you need the length.
// The struct has no overhead over a char* + separate size_t — it just bundles them.
// This pattern is used throughout systems programming (e.g. Go's string type).
