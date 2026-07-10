/*
 * How do strings work in C?
 *
 * C strings are null-terminated char arrays.  The null
 * character ('\0') marks the end.  String literals like
 * "hello" include the null terminator automatically.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    /* A string literal -- stored in read-only memory */
    const char *greeting = "Hello, C!";
    printf("String literal: \"%s\"\n", greeting);

    /* A mutable char array initialised from a literal */
    char buffer[32] = "World";
    printf("Char array:      \"%s\"\n", buffer);

    /* sizeof gives the array capacity, strlen gives string length */
    printf("sizeof buffer         = %zu bytes\n", sizeof(buffer));
    printf("strlen(\"World\")        = %zu chars (no null)\n", strlen("World"));
    printf("strlen(buffer)        = %zu chars\n", strlen(buffer));

    /* Manual construction */
    char manual[6];
    manual[0] = 'H';
    manual[1] = 'e';
    manual[2] = 'l';
    manual[3] = 'l';
    manual[4] = 'o';
    manual[5] = '\0';  /* null terminator -- required! */
    printf("Manual string:   \"%s\"\n", manual);

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * The null terminator is what distinguishes a string from a
 * plain char array.  Every function that works with strings
 * (<string.h>, printf with %s) scans until it finds '\0'.
 * Forgetting the null terminator is one of the most common
 * C bugs -- the function will keep reading past the array
 * boundary until it happens to find a zero byte.
 * ============================================================
 */


// 💡 Thinking in C:
// C strings are char arrays terminated by backslash-zero. strlen counts up to but not including the terminator.
