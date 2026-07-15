/*
 * Exercise 05 — Zero Copy
 *
 * Print all substrings separated by spaces without copying the original string.
 * Walk through with two pointers (start and end).
 *
 * Expected output:
 *   apple
 *   banana
 *   cherry
 *
 * Hints:
 *   - char str[] = "apple banana cherry";
 *   - Use char *start = str, then find next space → print with %.*s
 *   - Or temporarily replace spaces with '\0' and print each slice
 *   - Move start past the space and repeat until '\0'
 *   - #include <stdio.h>, <stdlib.h>, <stddef.h>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(void)
{
    // Your code here
    return EXIT_SUCCESS;
}