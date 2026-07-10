/*
 * How do I compile and run a C program?
 *
 * Compilation translates human-readable C into machine code.
 * A typical invocation looks like:
 *
 *     gcc -std=c11 -Wall -Wextra -pedantic -Werror -o program file.c
 *
 *   -std=c11    Use the C11 standard.
 *   -Wall       Enable most common warnings.
 *   -Wextra     Enable extra warnings.
 *   -pedantic   Reject non-standard extensions.
 *   -Werror     Treat every warning as an error.
 *   -o program  Name the output binary (default: a.out).
 *
 * Then run:  ./program
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("This program was compiled with:\n");
    printf("  Compiler: %s\n", __VERSION__);
    printf("  Standard: C11 (__STDC_VERSION__ = %ld)\n", (long)__STDC_VERSION__);
    printf("  Date:     %s at %s\n", __DATE__, __TIME__);

    printf("\nTypical build command for this file:\n");
    printf("  gcc -std=c11 -Wall -Wextra -pedantic -Werror -o compile compile.c\n");
    printf("  ./compile\n");

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * The compiler is your first line of defence.  -Wall -Wextra
 * -pedantic -Werror turns on almost every diagnostic the
 * compiler has and forces you to resolve each one.  It feels
 * picky at first, but every warning the compiler catches is a
 * bug that never reaches runtime.
 * ============================================================
 */

// 💡 Thinking in C:
// Compilation: source.c → object file → executable. Every warning is a potential bug.
