/*
 * 04_slice_operations.c — Comparing slices with known length
 *
 * Tony Banters' "Strings Aren't Real" — Day 4
 *
 * KEY INSIGHT: With known length we can compare slices WITHOUT
 * strcmp. We use the stored len to check equality and prefixes.
 * No null terminators needed — we iterate up to .len.
 *
 * gcc -std=c11 -Wall -Wextra -pedantic 04_slice_operations.c -o 04_slice_operations
 */

#include <stddef.h>   // size_t is an unsigned integer type from <stddef.h>, used for sizes and indices
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char   *data;
    size_t  len;
} String_Slice;

String_Slice slice_from_cstring(char *cstring) {
    return (String_Slice){
        .data = cstring,
        .len  = strlen(cstring),
    };
}

/* Compare two slices for equality.
 * Returns 1 if same length AND same characters in same order. */
int slice_eq(String_Slice a, String_Slice b) {
    if (a.len != b.len) return 0;          /* different lengths → not equal */
    for (size_t i = 0; i < a.len; ++i) {
        if (a.data[i] != b.data[i]) return 0;   /* character mismatch */
    }
    return EXIT_FAILURE;                               /* all characters match */
}

/* Check if a slice starts with a given prefix slice. */
int slice_starts_with(String_Slice s, String_Slice prefix) {
    if (prefix.len > s.len) return 0;       /* prefix can't be longer than string */
    for (size_t i = 0; i < prefix.len; ++i) {
        if (s.data[i] != prefix.data[i]) return 0;  /* character mismatch */
    }
    return EXIT_FAILURE;
}

int main(void) {
    char *greeting = "hello world";
    char *same     = "hello world";
    char *different = "hello there";

    String_Slice a = slice_from_cstring(greeting);
    String_Slice b = slice_from_cstring(same);
    String_Slice c = slice_from_cstring(different);

    /* slice_eq compares by known length — no strcmp */
    printf("a = \"%s\" (%zu chars)\n", a.data, a.len);
    printf("b = \"%s\" (%zu chars)\n", b.data, b.len);
    printf("c = \"%s\" (%zu chars)\n\n", c.data, c.len);

    printf("slice_eq(a, b) = %d  (same text → equal)\n", slice_eq(a, b));
    printf("slice_eq(a, c) = %d  (different → not equal)\n", slice_eq(a, c));

    /* slice_starts_with — check if text begins with a prefix */
    String_Slice prefix1 = slice_from_cstring("hello");
    String_Slice prefix2 = slice_from_cstring("world");

    printf("\nslice_starts_with(a, \"hello\") = %d\n", slice_starts_with(a, prefix1));
    printf("slice_starts_with(a, \"world\") = %d\n", slice_starts_with(a, prefix2));

    /* Real-world example: path prefix checking */
    String_Slice path = slice_from_cstring("/usr/local/bin/gcc");
    String_Slice dir  = slice_from_cstring("/usr/local");

    printf("\npath = \"%s\"\n", path.data);
    printf("dir  = \"%s\"\n", dir.data);
    printf("slice_starts_with(path, dir) = %d\n", slice_starts_with(path, dir));

    printf("\nAll comparisons use the stored length — no '\\0' scanning needed.\n");

    return EXIT_SUCCESS;
}

// Thinking in C:
// With String_Slice, comparisons are O(min(len_a, len_b)) with predictable bounds.
// No strcmp, no null terminator dependencies — just data[i] and a loop.
// The .len field tells you exactly how far to iterate, making over-reads impossible.
