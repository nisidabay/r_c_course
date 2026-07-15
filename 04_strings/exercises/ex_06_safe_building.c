/*
 * Exercise 06 — Safe Building
 *
 * Build a "Hello, [name]!" string using snprintf to avoid buffer overflow.
 *
 * Expected output:
 *   Hello, Alice!
 *
 * Hints:
 *   - char greeting[64];
 *   - snprintf(greeting, sizeof(greeting), "Hello, %s!", "Alice");
 *   - printf("%s\n", greeting);
 *   - #include <stdio.h>, <stdlib.h>, <stddef.h>
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(void)
{
    // Your code here
    return EXIT_SUCCESS;
}