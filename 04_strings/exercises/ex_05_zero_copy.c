/*
 * Exercise 05 — Zero Copy
 *
 * Implement slice_take and slice_drop — zero-copy slicing that creates
 * new String_Slice values by adjusting the data pointer and length.
 * NO malloc, NO memcpy, NO character copying.
 *
 * Expected output:
 *   Original:  "hello world"  (data = 0x..., len = 11)
 *
 *   slice_take(full, 5):  "hello"  (data = 0x..., len = 5)  <- SAME data pointer
 *   slice_drop(full, 6):  "world"  (data = 0x..., len = 5)  <- data pointer ADVANCED by 6
 *   slice_take(slice_drop(full, 6), 5):  "world"  (data = 0x..., len = 5)
 *
 * Hints:
 *   - Reuse String_Slice and slice_from_cstring from earlier exercises
 *   - slice_take(s, n): if n > s.len, n = s.len; return { s.data, n }
 *   - slice_drop(s, n): if n > s.len, n = s.len; return { s.data + n, s.len - n }
 *   - print_slice(s): helper that prints characters using s.len
 *   - Use %p to print the data pointer and verify zero-copy
 *   - #include <stddef.h>, <stdio.h>, <stdlib.h>, <string.h>
 */

#include <stddef.h>   // size_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Your code here

int main(void)
{
    char *text = "hello world";

    // Your code here

    return EXIT_SUCCESS;
}
