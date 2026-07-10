/*
 * How do I measure and compare strings?
 *
 * strlen returns the length (without the null terminator).
 * strcmp compares lexicographically.  Both scan until '\0'.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char *s1 = "apple";
    const char *s2 = "banana";
    const char *s3 = "apple";

    /* strlen -- counts chars before the null */
    printf("strlen(\"%s\") = %zu\n", s1, strlen(s1));
    printf("strlen(\"%s\") = %zu\n", s2, strlen(s2));

    /* strcmp -- returns 0 if equal, <0 if first is less, >0 if greater */
    const int cmp1 = strcmp(s1, s2);
    printf("strcmp(\"%s\", \"%s\") = %d\n", s1, s2, cmp1);

    const int cmp2 = strcmp(s1, s3);
    printf("strcmp(\"%s\", \"%s\") = %d\n", s1, s3, cmp2);

    /* Manual iteration to measure length */
    const char *p = s2;
    size_t len = 0;
    while (*p != '\0') {
        ++len;
        ++p;
    }
    printf("Manual strlen(\"%s\") = %zu\n", s2, len);

    /* Manual comparison */
    const char *a = "abc";
    const char *b = "abd";
    size_t i = 0;
    int diff = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            diff = (unsigned char)a[i] - (unsigned char)b[i];
            break;
        }
        ++i;
    }
    if (diff == 0 && a[i] != b[i]) {
        diff = (a[i] == '\0') ? -1 : 1;
    }
    printf("Manual strcmp(\"%s\", \"%s\") = %d\n", a, b, diff);

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * strcmp returns 0 for equality -- this trips up newcomers
 * who write  if (strcmp(a, b))  thinking it means "equal".
 * It actually means "not equal" because 0 is false in C.
 * Always write  if (strcmp(a, b) == 0)  for equality checks.
 * ============================================================
 */


// 💡 Thinking in C:
// strlen for length, strcmp for comparison (returns 0 on match), strstr for search.
