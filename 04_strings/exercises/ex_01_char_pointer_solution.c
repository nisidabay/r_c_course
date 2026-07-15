/*
 * Exercise 01: char* is a pointer (8 bytes), not a string — SOLUTION
 *
 * Concept: A char* is just a pointer (8 bytes on 64-bit).
 *          String literals are read-only arrays of char. sizeof
 *          on a pointer tells you the pointer width, not the text length.
 *
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_01_char_pointer.c -o ex_01_char_pointer
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *greeting = "hello";
    char  arr[]    = "hello";

    /* sizeof on a pointer is always the same — the pointer width */
    printf("sizeof(char*) = %zu bytes\n", sizeof(char *));

    printf("sizeof(greeting) = %zu (pointer width — always 8 on 64-bit)\n",
           sizeof(greeting));

    /* sizeof on an array includes every byte including the null terminator */
    printf("sizeof(arr) = %zu (array size — includes '\\0')\n",
           sizeof(arr));

    /* strlen has to scan — always O(n) */
    printf("strlen(greeting) = %zu (must scan %zu chars looking for '\\0')\n",
           strlen(greeting), strlen(greeting));

    /* String literals are read-only — can't modify */
    printf("\nString literals live in read-only memory.\n");
    printf("Uncommenting greeting[0] = 'H' would segfault.\n");

    return EXIT_SUCCESS;
}
