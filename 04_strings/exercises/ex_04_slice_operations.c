/*
 * Exercise 04: Comparing slices with known length
 *
 * Concept: With known length we can compare slices WITHOUT strcmp.
 *          We use the stored len to check equality and prefixes.
 *          No null terminators needed — we iterate up to .len.
 *
 * Fill in the blanks (marked BLANK) to complete slice_eq and
 * slice_starts_with. Both functions use the stored length to
 * bound their loops.
 *
 * Note: Exercises 03+ use size_t (from <stddef.h>).
 *
 * Safe C Standard: no strcpy/strcat/sprintf/scanf/atoi/atof.
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_04_slice_operations.c -o ex_04_slice_operations
 */

#include <stddef.h>   // size_t is an unsigned integer type from <stddef.h>, used for sizes and indices
#include <stdio.h>
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
    if (/*@*/) return 0;          /* different lengths → not equal */
    for (size_t i = 0; i < a.len; ++i) {
        if (/*@*/) return 0;      /* character mismatch */
    }
    return 1;                      /* all characters match */
}

/* Check if a slice starts with a given prefix slice. */
int slice_starts_with(String_Slice s, String_Slice prefix) {
    if (/*@*/) return 0;          /* prefix can't be longer than string */
    for (size_t i = 0; i < prefix.len; ++i) {
        if (/*@*/) return 0;      /* character mismatch */
    }
    return 1;
}

int main(void) {
    char *greeting = "hello world";
    char *same     = "hello world";
    char *different = "hello there";

    String_Slice a = slice_from_cstring(greeting);
    String_Slice b = slice_from_cstring(same);
    String_Slice c = slice_from_cstring(different);

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

    return 0;
}
