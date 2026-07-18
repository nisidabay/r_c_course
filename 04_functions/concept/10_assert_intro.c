/*
 * 10_assert_intro.c — Assert: the simplest debugging tool in C
 * Group 04 — Functions
 *
 * assert(expr) from <assert.h> checks an expression at runtime.  If
 * the expression is false (zero), assert prints a message to stderr
 * and calls abort() to terminate the program.
 *
 *   assert(ptr != NULL);   // crash NOW if null, not 50 lines later
 *
 * Unlike if/else error handling, assert is for conditions that should
 * NEVER happen -- programming errors, not user errors.
 *
 * When you define NDEBUG before including <assert.h>, all assert calls
 * become no-ops.  This lets you keep sanity checks in your code during
 * development and strip them in release builds.
 */

#include <assert.h>   /* assert() macro */
#include <stdio.h>
#include <stdlib.h>

/*
 * A simple example: division with a precondition.
 * The divisor must not be zero — that's a programming error, not
 * something we handle gracefully at runtime.
 */
static int divide(int a, int b)
{
    assert(b != 0);       /* crash if b is zero */
    return a / b;
}

/*
 * sum_array — sum elements of an array.
 * The pointer must not be NULL, and the size must be positive.
 */
static int sum_array(const int *arr, size_t n)
{
    assert(arr != NULL);   /* NULL pointer = bug */
    assert(n > 0);         /* empty array = probably a bug */

    int sum = 0;
    for (size_t i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

int main(void)
{
    printf("=== assert() — Debugging by Contract ===\n\n");

    /* These work fine */
    int values[] = {10, 20, 30};
    int total = sum_array(values, 3);
    printf("sum_array(values, 3) = %d\n\n", total);

    printf("divide(10, 2) = %d\n\n", divide(10, 2));

    /* What happens when we violate a precondition?
     *
     * Uncomment one of these to see assert in action:
     *
     *   int *null_ptr = NULL;
     *   sum_array(null_ptr, 3);    // assert(NULL != NULL) -> abort!
     *
     *   sum_array(values, 0);      // assert(0 > 0) -> abort!
     *
     *   divide(10, 0);             // assert(0 != 0) -> abort!
     */

    printf("To see assert in action, uncomment one of the dangerous\n");
    printf("calls in the source and recompile.\n");

    return EXIT_SUCCESS;
}

// Thinking in C:
// assert is a MACRO, not a function.  That's why it can use
// __FILE__, __LINE__, and __func__ to report exactly where
// the failure happened.
//
// When to use assert vs if/else:
//
//   assert(b != 0);       // "this should NEVER happen"
//   if (b == 0) {         // "this CAN happen (bad user input)"
//       fprintf(stderr, "Cannot divide by zero\n");
//       return -1;
//   }
//
// Use assert for INVARIANTS — conditions that must be true if
// the program is correct.  Use if/else for EXPECTED errors —
// bad input, missing files, network failures.
//
// The first thing experienced C developers do when debugging
// is add asserts.  They're cheaper than debuggers and catch
// bugs at the source, not at the symptom.
