/*
 * 08_lenstr.c — Manual strlen implementation
 * Group 04 - Strings
 *
 * strlen counts characters by walking a pointer forward until it
 * hits the null terminator '\0'.  This is the simplest possible
 * pointer traversal and the foundation for understanding how
 * C strings work at the hardware level.
 */

#include <stdio.h>
#include <stdlib.h>

/* ---- manual strlen: walk pointer until '\0' ---- */
static int lenstr(const char *s)
{
    int n = 0;
    while (*s != '\0') {
        n++;
        s++;
    }
    return n;
}

int main(void)
{
    const char *test = "Hello, world!";

    int len = lenstr(test);

    printf("String: \"%s\"\n", test);
    printf("Length: %d\n", len);

    /* Verify against the standard library version */
    if ((size_t)len == sizeof("Hello, world!") - 1) {
        puts("Match — result equals built-in strlen behavior.");
    } else {
        puts("Mismatch!");
    }

    /* Test edge cases */
    printf("\nEdge cases:\n");
    printf("  lenstr(\"\")           = %d  (empty string)\n", lenstr(""));
    printf("  lenstr(\"a\")          = %d  (single char)\n",     lenstr("a"));
    printf("  lenstr(\"abc\")        = %d  (short string)\n",   lenstr("abc"));

    return EXIT_SUCCESS;
}

// Thinking in C:
// A C string is a pointer to a sequence of bytes ending with '\0'.
// strlen walks from the start until it hits the zero byte — that's
// O(n) every time, which is why repeated strlen on the same string
// in a loop is O(n^2).  Understanding this at the pointer level
// is the key to writing efficient string code in C.
