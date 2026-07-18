/*
 * Exercise 09 — Manual strlen (lenstr)
 *
 * Implement lenstr() manually by walking a pointer until '\0',
 * then verify your implementation against the standard strlen for
 * several test strings (empty, single char, short string, a sentence).
 *
 * Expected output:
 *   Testing lenstr:
 *     ""       -> 0  (strlen says 0)
 *     "a"      -> 1  (strlen says 1)
 *     "abc"    -> 3  (strlen says 3)
 *     "Hello, world!" -> 13 (strlen says 13)
 *   All match — lenstr works correctly!
 *
 * Hints:
 *   - int lenstr(const char *s) { int n = 0; while (*s != '\0') { n++; s++; } return n; }
 *   - Compare with strlen(s) wrapped in (int) or (size_t)
 *   - Use an array of test strings for cleaner code
 *   - #include <stdio.h>, <stdlib.h>, <string.h>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Your code here

int main(void)
{
    // Your code here

    return EXIT_SUCCESS;
}
