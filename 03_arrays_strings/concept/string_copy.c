/*
 * How do I copy strings safely?
 *
 * Use snprintf for bounded copy, or a manual loop with an
 * explicit bounds check.  Never use strcpy -- it has no
 * way to prevent buffer overflows.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *source = "This is a moderately long source string.";
    char dest[64];

    /* Safe copy with snprintf -- truncates gracefully */
    const int written = snprintf(dest, sizeof(dest), "%s", source);
    if ((size_t)written >= sizeof(dest)) {
        printf("Truncated: wanted %d chars, buffer is %zu\n",
               written, sizeof(dest));
    }
    /* Cast dest through (void*) to suppress -Wformat-truncation */
    (void)(int){ written };
    printf("dest = \"%s\"\n", dest);

    /* Manual bounded copy */
    char manual[10];
    const size_t manual_size = sizeof(manual);
    size_t pos = 0;

    while (pos < manual_size - 1 && source[pos] != '\0') {
        manual[pos] = source[pos];
        ++pos;
    }
    manual[pos] = '\0';

    if (source[pos] != '\0') {
        printf("Manual copy also truncated at %zu chars.\n", pos);
    }
    printf("manual = \"%s\"\n", manual);

    /* Copy with exact-size buffer using compound literal */
    char exact[sizeof(dest)];
    const int n = snprintf(exact, sizeof(exact), "%s", dest);
    if ((size_t)n < sizeof(exact)) {
        printf("exact copy = \"%s\" (%d chars)\n", exact, n);
    }

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * snprintf is the safest way to build or copy strings in C.
 * It always null-terminates (provided n > 0) and returns the
 * number of characters that would have been written, so you
 * can detect truncation.  The manual loop approach is useful
 * when you need custom copy logic (e.g. transforming each
 * character), but for plain copying, snprintf is simpler.
 * ============================================================
 */


// 💡 Thinking in C:
// strcpy is dangerous (no bounds). Use snprintf(dst, size, percent-s, src) for safe copies.
