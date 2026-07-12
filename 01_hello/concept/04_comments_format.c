#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // This is a single-line comment -- the compiler ignores everything after //
    printf("Single-line comments use //\n");

    /*
     * This is a multi-line comment.
     * Everything between slash-star and star-slash is ignored.
     * Useful for longer explanations or temporarily disabling code.
     */
    printf("Multi-line comments use slash-star and star-slash\n");

    /* Comments can also appear mid-line */ printf("Inline comment works\n");

    // Blank lines and indentation make code readable:
    int x = 10;
    int y = 20;

    int total = x + y;

    printf("Total: %d\n", total);

    return EXIT_SUCCESS;
}

// Thinking in C: Comments exist only for humans -- the compiler strips them
// before generating code. Unlike some languages, C has no docstring or
// documentation comment standard built in. Indentation is recommended for
// readability but has no syntactic meaning in C. Good formatting is a
// discipline, not enforced by the language itself.
