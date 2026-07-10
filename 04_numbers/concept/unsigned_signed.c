/*
 * How do signed and unsigned integers differ?
 *
 * Signed integers can represent negative values.  Unsigned
 * wrap around at zero (modular arithmetic).  Signed overflow
 * is undefined behaviour -- the compiler can do anything.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Unsigned wrap-around */
    unsigned int u = 0;
    printf("Unsigned wrap-around:\n");
    u = u - 1;
    printf("  0 - 1 = %u  (wraps to max)\n", u);
    u = u + 1;
    printf("  max + 1 = %u  (wraps to 0)\n", u);

    /* Signed overflow is UB -- but typical behaviour shown */
    int si = 2147483640;  /* near INT_MAX */
    printf("\nSigned overflow (UB!):\n");
    printf("  Starting: %d\n", si);
    for (int i = 0; i < 10; ++i) {
        si = si + 1;
        printf("  %d\n", si);
    }

    /* Comparing signed vs unsigned is dangerous */
    const int      signed_val   = -1;
    const unsigned unsigned_val = 0;

    printf("\nSigned/unsigned comparison trap:\n");
    /* Explicit cast avoids -Wsign-compare: compare as signed */
    if (signed_val < (int)unsigned_val) {
        printf("  -1 < 0  (signed comparison -- correct)\n");
    } else {
        printf("  -1 >= 0 (unsigned comparison -- WRONG!)\n");
    }

    const int a = 10;
    const unsigned b = 20;
    const int sum = a + (int)b;  /* explicit cast */
    printf("\nSafe mixed arithmetic: %d + %u = %d\n", a, b, sum);

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * When a signed and unsigned value appear in the same
 * expression, the signed value is implicitly converted to
 * unsigned (the "usual arithmetic conversions").  This can
 * turn -1 into a very large positive number.  Compilers
 * warn about this with -Wsign-compare (included in -Wextra).
 * Never ignore that warning.
 * ============================================================
 */


// 💡 Thinking in C:
// Unsigned wraps around predictably. Signed overflow is undefined behavior. Know the difference.
