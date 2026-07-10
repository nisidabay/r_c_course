/*
 * How do I define and call functions?
 *
 * Functions group reusable logic.  A function has a return
 * type, a name, parameters, and a body.  static helper
 * functions are private to this translation unit.
 */

#include <stdio.h>
#include <stdlib.h>

/* Forward declaration so main can call it */
static int add(int a, int b);

/* Helper: compute the absolute value of an integer */
static int abs_val(int x) {
    return (x < 0) ? -x : x;
}

/* Helper: print a line of dashes */
static void print_line(size_t count) {
    for (size_t i = 0; i < count; ++i) {
        putchar('-');
    }
    putchar('\n');
}

int main(void) {
    const int result = add(7, 5);
    printf("7 + 5 = %d\n", result);

    printf("abs_val(-3) = %d\n", abs_val(-3));
    printf("abs_val(42) = %d\n", abs_val(42));

    print_line(20);
    printf("  Functions FTW!\n");
    print_line(20);

    return EXIT_SUCCESS;
}

/* Define add after main -- the forward declaration makes it work */
static int add(int a, int b) {
    return a + b;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * C compiles each translation unit (.c file) independently.
 * A function must be declared before its first use.  Forward
 * declarations let you place main() first and define helpers
 * after -- this improves readability because the reader sees
 * the top-level logic before the details.  Mark functions
 * static when they are only used within the same file.
 * ============================================================
 */


// 💡 Thinking in C:
// Functions group logic. int add(int a, int b) { return a + b; } — input, output, name.
