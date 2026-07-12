/*
 * Concept: Scope — Local vs Global Variables, Block Scope
 * Group 03 - Functions
 *
 * "Scope" is where a variable is visible in your program.
 *   - Global scope: visible everywhere after declaration
 *   - Local/block scope: visible only inside the { } where it's declared
 *
 * Inner scopes can "shadow" outer names (not recommended in practice).
 */

#include <stdio.h>
#include <stdlib.h>

/* ---- global scope ---- */
/* visible to every function in this file (after this point) */
int global_count = 0;

void count_up(void)
{
    global_count = global_count + 1;   /* modifies the global */
    /* local variable with same name — shadows the global inside this block */
    int global_count = 99;
    printf("  Inside count_up (local): global_count = %d\n", global_count);
    /* the local 'global_count' hides the real global: 99 prints */
}

void see_global(void)
{
    printf("  Inside see_global: global_count = %d\n", global_count);
    /* here there is no local shadow, so the real global is visible */
}

int main(void)
{
    puts("=== Scope Demo ===");

    printf("Initial global_count: %d\n", global_count);

    /* local variable in main */
    int local_val = 42;
    printf("In main, local_val = %d\n", local_val);

    count_up();     /* shadowing inside — prints 99, but real global stays 1 */
    see_global();   /* confirms global is now 1, not 99 */

    printf("\n--- block scope ---\n");

    int block_demo = 1;
    printf("Before block: block_demo = %d\n", block_demo);

    {
        /* new block — new scope */
        int block_demo = 2;   /* shadows outer block_demo */
        int inner_only = 3;
        printf("Inside block: block_demo = %d, inner_only = %d\n",
               block_demo, inner_only);
    }

    /* inner_only is gone — out of scope */
    /* block_demo is the outer one again */
    printf("After block:  block_demo = %d\n", block_demo);

    return EXIT_SUCCESS;
}

// Thinking in C:
// C has simple scope rules: { } delimit scopes, a variable lives from
// its declaration to the closing brace.  Globals live for the whole
// program.  Shadowing (hiding an outer name with an inner one) compiles
// with a warning under -Wshadow — C lets you do it, but clarity suffers.
