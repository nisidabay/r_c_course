/*
 * How do I parse integers safely with strtol?
 *
 * strtol (string to long) provides full error checking:
 * invalid input, trailing garbage, and range errors.
 * Always check errno and the end pointer.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(void) {
    const char *inputs[] = {
        "1234",
        "   -567",
        "0x1F",
        "99999999999999999999999",
        "abc",
        "42extra",
        ""
    };
    const size_t count = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < count; ++i) {
        const char *str = inputs[i];
        char *endptr = NULL;

        errno = 0;
        const long val = strtol(str, &endptr, 0);

        if (errno == ERANGE) {
            printf("input \"%s\": out of range\n", str);
        } else if (endptr == str) {
            printf("input \"%s\": no digits found\n", str);
        } else if (*endptr != '\0') {
            printf("input \"%s\": parsed %ld, trailing \"%s\"\n",
                   str, val, endptr);
        } else {
            printf("input \"%s\": parsed %ld\n", str, val);
        }
    }

    /* strtol with explicit base */
    printf("\n--- strtol with base 16 ---\n");
    const char *hex = "FF";
    char *ep = NULL;
    const long hex_val = strtol(hex, &ep, 16);
    if (ep != hex && *ep == '\0') {
        printf("0x%s = %ld\n", hex, hex_val);
    }

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * strtol is the safe alternative to atoi.  atoi returns 0 on
 * error but also returns 0 for valid input "0" -- you can't
 * tell the difference.  strtol gives you three independent
 * error signals: endptr (no digits), errno == ERANGE (overflow),
 * and *endptr (trailing garbage).  Use strtoll for long long,
 * strtoul/strtoull for unsigned variants.
 * ============================================================
 */


// 💡 Thinking in C:
// strtol is the safe way to parse integers. Always check errno and the end pointer.
