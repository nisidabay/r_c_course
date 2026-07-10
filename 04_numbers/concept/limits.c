/*
 * How do I use the integer limits from <limits.h>?
 *
 * <limits.h> defines the minimum and maximum values for
 * each integer type.  These are compile-time constants
 * that help with overflow checks and portable code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>
#include <inttypes.h>

int main(void) {
    printf("=== Limits from <limits.h> ===\n");
    printf("CHAR_BIT     = %d\n",    CHAR_BIT);
    printf("SCHAR_MIN    = %d\n",    SCHAR_MIN);
    printf("SCHAR_MAX    = %d\n",    SCHAR_MAX);
    printf("UCHAR_MAX    = %u\n",    UCHAR_MAX);
    printf("SHRT_MIN     = %d\n",    SHRT_MIN);
    printf("SHRT_MAX     = %d\n",    SHRT_MAX);
    printf("USHRT_MAX    = %u\n",    USHRT_MAX);
    printf("INT_MIN      = %d\n",    INT_MIN);
    printf("INT_MAX      = %d\n",    INT_MAX);
    printf("UINT_MAX     = %u\n",    UINT_MAX);
    printf("LONG_MIN     = %ld\n",   LONG_MIN);
    printf("LONG_MAX     = %ld\n",   LONG_MAX);
    printf("ULONG_MAX    = %lu\n",   ULONG_MAX);
    printf("LLONG_MIN    = %lld\n",  LLONG_MIN);
    printf("LLONG_MAX    = %lld\n",  LLONG_MAX);
    printf("ULLONG_MAX   = %llu\n",  ULLONG_MAX);

    printf("\n=== Fixed-width limits from <stdint.h> ===\n");
    printf("INT32_MIN    = %" PRId32 "\n", INT32_MIN);
    printf("INT32_MAX    = %" PRId32 "\n", INT32_MAX);
    printf("UINT32_MAX   = %" PRIu32 "\n", UINT32_MAX);
    printf("INT64_MIN    = %" PRId64 "\n", INT64_MIN);
    printf("INT64_MAX    = %" PRId64 "\n", INT64_MAX);
    printf("UINT64_MAX   = %" PRIu64 "\n", UINT64_MAX);

    /* Using limits for overflow checks */
    printf("\n=== Overflow checks ===\n");
    if (1000000 < INT_MAX - 2000000) {
        printf("1000000 + 2000000 fits in int.\n");
    }

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * The limits in <limits.h> are the minimum/maximum values
 * that each type can hold on the current platform.  They are
 * essential for overflow detection (see overflow.c).  The
 * fixed-width limits from <stdint.h> (INT32_MIN, etc.) are
 * constant across platforms and preferred for portable code
 * that uses fixed-width types.
 * ============================================================
 */


// 💡 Thinking in C:
// limits.h defines INT_MIN, INT_MAX, etc. Know your platform bounds before doing arithmetic.
