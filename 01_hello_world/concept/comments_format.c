/*
 * How do I write comments and format my code?
 *
 * Comments make code understandable to humans.  Consistent
 * indentation makes structure visible.
 *
 * Two comment styles in C:
 *   // text            -- single-line comment (C99+)
 *   delimited block   -- multi-line comment: slash-star ... star-slash
 */

#include <stdio.h>
#include <stdlib.h>

/* Helper: print a diamond-shaped separator line */
static void print_separator(size_t width) {
    for (size_t i = 0; i < width; ++i) {
        putchar('-');
    }
    putchar('\n');
}

/* Helper: print an indented line at a given level */
static void print_indented(const char *line, size_t level) {
    for (size_t i = 0; i < level; ++i) {
        putchar(' ');
        putchar(' ');
    }
    printf("%s\n", line);
}

int main(void) {
    /* ----  Single-line comments  ---- */
    // These start with // and extend to end of line.
    // Use them for brief notes on the line above or beside code.

    print_separator(40);
    print_indented("Single-line  //  -- short explanations", 1);
    print_indented("Multi-line  /* */ -- longer descriptions", 1);
    print_indented("Indentation -- consistent every 2 or 4 spaces", 1);
    print_separator(40);

    /* Multi-line comments let you write longer notes.      */
    /* Every line starts with * to keep it readable.         */
    /*                                                       */
    /* Indent consistently: 2 or 4 spaces per level.        */
    /* Stick to one style throughout the project.            */

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * Comments are for WHY, not WHAT.  The code already shows WHAT
 * it does.  A good comment explains the reasoning behind a
 * choice, warns about a subtle edge case, or documents the
 * expected contract of a function.  Consistent indentation is
 * the cheapest, most effective form of readability.
 * ============================================================
 */

// 💡 Thinking in C:
// printf format strings match types: %d for int, %f for double, %s for string.
