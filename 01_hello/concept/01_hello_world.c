#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello, World!\n");
    return EXIT_SUCCESS;
}

// Thinking in C:
// C is a compiled language — every program starts in main().
// Unlike Python or JavaScript, C has no REPL; you write, compile, then run.
// printf() is not built into the language — it comes from the stdio library.
// The \n is an escape sequence for a newline; without it output stays on one line.
// return 0 signals success to the operating system.
