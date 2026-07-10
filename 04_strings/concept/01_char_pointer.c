/*
 * 01_char_pointer.c — char* is a POINTER, not a string
 *
 * Tony Banters' "Strings Aren't Real" — Day 1
 *
 * KEY INSIGHT: A char* is just a pointer (8 bytes on 64-bit).
 * There is NO string type in C. "String literals" are arrays of
 * char that C lets you point at with a char*. If you try to
 * modify one, the program crashes (segfault).
 *
 * gcc -std=c11 -Wall -Wextra -pedantic 01_char_pointer.c -o 01_char_pointer
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    /* char* is a pointer — always 8 bytes on 64-bit systems */
    char *greeting = "hello";
    char *name     = "world";
    char *path     = "/usr/share/dict/words";

    printf("sizeof(char*) = %zu bytes  (a pointer, always)\n\n", sizeof(char *));

    printf("greeting = %p  sizeof(greeting) = %zu  strlen = %zu  data: %s\n",
           (void *)greeting, sizeof(greeting), strlen(greeting), greeting);
    printf("name     = %p  sizeof(name)     = %zu  strlen = %zu  data: %s\n",
           (void *)name,     sizeof(name),     strlen(name),     name);
    printf("path     = %p  sizeof(path)     = %zu  strlen = %zu  data: %s\n",
           (void *)path,     sizeof(path),     strlen(path),     path);

    printf("\nsizeof is always %zu, no matter how long the string.\n", sizeof(greeting));
    printf("sizeof tells you the POINTER size, NOT the string length.\n");

    /* strlen must WALK the whole string to find the length */
    printf("\nstrlen(\"%s\") had to scan %zu characters looking for '\\0'.\n",
           greeting, strlen(greeting));

    /* Demonstrating that string literals are read-only */
    printf("\nAttempting to modify a string literal... (this will segfault)\n");

    /* UNCOMMENT the next line to see the crash:
     * greeting[0] = 'H';   // BOOM — segfault; string literals live in read-only memory
     */

    printf("(That line is commented out — the program survived.)\n");

    /* Array vs pointer: sizeof behaves differently */
    char arr[] = "hello";
    printf("\nBut with an ARRAY: sizeof(arr) = %zu  (includes '\\0')\n", sizeof(arr));
    printf("Arrays are NOT pointers, even though they decay into them.\n");

    return 0;
}

// Thinking in C:
// char* is just a pointer (8 bytes). There is no string type.
// sizeof never gives you the length of the text — just the pointer width.
// strlen must O(n)-scan for '\0' because C doesn't know where the string ends.
// This is the root of almost every C string bug.
