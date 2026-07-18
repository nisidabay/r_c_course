/*
 * Exercise 04 — Slice Operations
 *
 * Implement slice_eq and slice_starts_with using String_Slice's stored
 * length — compare without scanning for '\0'.
 *
 * Expected output:
 *   a = "hello world" (11 chars)
 *   b = "hello world" (11 chars)
 *   c = "hello there" (11 chars)
 *
 *   slice_eq(a, b) = 1  (same text → equal)
 *   slice_eq(a, c) = 0  (different → not equal)
 *
 *   slice_starts_with(a, "hello") = 1
 *   slice_starts_with(a, "world") = 0
 *
 *   path = "/usr/local/bin/gcc"
 *   dir  = "/usr/local"
 *   slice_starts_with(path, dir) = 1
 *
 * Hints:
 *   - Reuse String_Slice and slice_from_cstring from Exercise 03
 *   - slice_eq(a, b): if lengths differ → 0, then compare char by char
 *   - slice_starts_with(s, prefix): if prefix.len > s.len → 0, then compare
 *   - Both return 1 for match, 0 for mismatch
 *   - #include <stddef.h>, <stdio.h>, <stdlib.h>, <string.h>
 */

#include <stddef.h>   // size_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Your code here

int main(void)
{
    char *greeting = "hello world";
    char *same     = "hello world";
    char *different = "hello there";

    // Your code here

    return EXIT_SUCCESS;
}
