/*
 * How do I detect integer overflow?
 *
 * Signed integer overflow is undefined behaviour.  You must
 * check before performing an operation, not after.  Use the
 * limits from <limits.h> or <stdint.h> for the checks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

/* Checked addition: returns 0 on success, -1 on overflow */
static int checked_add(int a, int b, int *result) {
    if ((b > 0 && a > INT_MAX - b) ||
        (b < 0 && a < INT_MIN - b)) {
        return -1;  /* overflow would occur */
    }
    *result = a + b;
    return 0;
}

/* Checked subtraction */
static int checked_sub(int a, int b, int *result) {
    if ((b > 0 && a < INT_MIN + b) ||
        (b < 0 && a > INT_MAX + b)) {
        return -1;
    }
    *result = a - b;
    return 0;
}

int main(void) {
    int result;

    /* Safe addition */
    if (checked_add(100000, 200000, &result) == 0) {
        printf("100000 + 200000 = %d\n", result);
    } else {
        printf("Overflow detected!\n");
    }

    /* Overflow detection */
    if (checked_add(INT_MAX, 1, &result) == 0) {
        printf("INT_MAX + 1 = %d\n", result);
    } else {
        printf("Overflow detected: INT_MAX + 1\n");
    }

    /* Subtraction */
    if (checked_sub(INT_MIN, 1, &result) == 0) {
        printf("INT_MIN - 1 = %d\n", result);
    } else {
        printf("Overflow detected: INT_MIN - 1\n");
    }

    /* Unsigned wraps predictably, but check is still possible */
    const unsigned ua = 4000000000U;
    const unsigned ub = 1000000000U;
    if (ua > UINT_MAX - ub) {
        printf("Unsigned overflow detected: %u + %u\n", ua, ub);
    } else {
        printf("Unsigned sum: %u\n", ua + ub);
    }

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * Signed overflow is UB -- the compiler may optimise away
 * your overflow check if you write it after the operation.
 * Always check before performing the arithmetic.  For
 * unsigned types, overflow wraps around predictably (modular
 * arithmetic), which is sometimes intentional (e.g. hash
 * functions).  The checked_add/checked_sub pattern above is
 * the portable way to detect signed overflow.
 * ============================================================
 */


// 💡 Thinking in C:
// Integer overflow is UB in C. Check before you compute, or use safe conversion functions.
