/*
 * Exercise 03 — String Slice
 *
 * Define the String_Slice struct (data + len) and use it to avoid
 * scanning for '\0' every time.
 *
 * Expected output:
 *   Old way:  "hello world"  strlen = 11  (O(n) every call)
 *   New way:  data = 0x...  len = 11  (O(1) — length is stored)
 *   Characters by known length:  hello world
 *
 * Hints:
 *   - #include <stddef.h>, <stdio.h>, <stdlib.h>, <string.h>
 *   - typedef struct { char *data; size_t len; } String_Slice;
 *   - String_Slice slice_from_cstring(char *cstring) { ... }
 *   - Use strlen ONCE in slice_from_cstring, store the result
 *   - Print characters with a for loop using s.len, not '\0'
 *   - size_t is unsigned, use %zu to print it
 */

#include <stddef.h>   // size_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Your code here

int main(void)
{
    char *greeting = "hello world";

    // Your code here

    return EXIT_SUCCESS;
}
