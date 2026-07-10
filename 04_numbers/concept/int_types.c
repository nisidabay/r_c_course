/*
 * How do I choose among integer types?
 *
 * C offers several integer types with different widths.
 * Use <stdint.h> for exact-size types when portability
 * matters.  sizeof tells you the size in bytes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <inttypes.h>

int main(void) {
    const short      s = 100;
    const int        i = 100000;
    const long       l = 100000L;
    const long long  ll = 10000000000LL;

    const int32_t    i32 = 2000000000;
    const int64_t    i64 = 9000000000000000000LL;

    printf("short:         %-4zd bytes, value = %hd\n",   sizeof(short),     s);
    printf("int:           %-4zd bytes, value = %d\n",     sizeof(int),       i);
    printf("long:          %-4zd bytes, value = %ld\n",    sizeof(long),      l);
    printf("long long:     %-4zd bytes, value = %lld\n",   sizeof(long long), ll);
    printf("int32_t:       %-4zd bytes, value = %" PRId32 "\n", sizeof(int32_t), i32);
    printf("int64_t:       %-4zd bytes, value = %" PRId64 "\n", sizeof(int64_t), i64);

    printf("\nPlatform pointer size: %zu bytes\n", sizeof(void *));

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * int is the "natural" word size of the platform (usually
 * 32 bits on 64-bit systems).  long may be 8 bytes on Linux
 * but 4 bytes on Windows.  For portable code that needs exact
 * sizes, use int32_t, uint64_t, etc. from <stdint.h>.  The
 * PRI macros (PRId32, PRIu64, etc.) provide portable format
 * specifiers for these types.
 * ============================================================
 */


// 💡 Thinking in C:
// int is signed and can overflow. Use fixed-width types (int32_t, uint64_t) when size matters.
