/*
 * Exercise 09 — Manual strlen (lenstr) — SOLUTION
 *
 * Implement lenstr() manually by walking a pointer until '\0',
 * then verify against the standard strlen for several test strings.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    const char *tests[] = {"", "a", "abc", "Hello, world!"};
    int all_match = 1;

    printf("Testing lenstr:\n");
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        int my_len = lenstr(tests[i]);
        size_t lib_len = strlen(tests[i]);
        printf("  \"%s\" -> %d  (strlen says %zu)%s\n",
               tests[i], my_len, lib_len,
               (size_t)my_len == lib_len ? "" : "  <-- MISMATCH!");
        if ((size_t)my_len != lib_len)
            all_match = 0;
    }

    if (all_match)
        printf("All match — lenstr works correctly!\n");

    return EXIT_SUCCESS;
}
