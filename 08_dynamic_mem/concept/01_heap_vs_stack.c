/*
 * 01_heap_vs_stack.c
 * Group 07 — Dynamic Memory
 * Concept: the static-size limit of stack arrays, why we need the heap
 *
 * Stack arrays have a fixed size chosen at compile time.  You cannot
 * grow them, and allocating too large a local array causes a stack
 * overflow (segfault at runtime).  This file demonstrates BOTH limits
 * so we understand WHY dynamic allocation exists — malloc is NOT used
 * here, only the problem.
 *
 * WARNING: the huge_local() function deliberately overflows the stack
 * on most systems and WILL crash.  Run with caution.
 */

#include <stdio.h>
#include <stdlib.h>

#define FIXED_SIZE 5

int main(void)
{
    /* --- Problem 1: fixed size cannot grow at runtime --- */
    int scores[FIXED_SIZE] = { 78, 85, 92 };
    size_t count = 3;

    printf("Fixed array of %d slots.\n", FIXED_SIZE);
    printf("Currently holding %zu scores.\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("  scores[%zu] = %d\n", i, scores[i]);
    }

    /* If the user enters 10 numbers, we cannot store them all.
     * There is no 'grow the array' operation on the stack. */
    printf("\nProblem: user wants to add 100 more scores...\n");
    printf("The fixed array cannot expand.  We need a different\n");
    printf("kind of storage — memory allocated at runtime.\n\n");

    /* --- Problem 2: large stack allocation crashes --- */
    printf("Now attempting a huge stack allocation (may crash)...\n");
    fflush(stdout);

    /* A few MB on stack is often fatal.  This is NOT a compile error;
     * the compiler happily accepts it because sizes are known.  Crash
     * happens when the function tries to run. */
    char huge[4 * 1024 * 1024];   /* 4 MB on the stack */
    huge[0] = 'A';
    printf("Huge stack allocation at %p (first byte: %c)\n",
           (void*)huge, huge[0]);
    /* ^ If you see this, your system has an unusually large stack.
     * Most compilers/OS combos will segment-fault before reaching
     * this printf. */

    printf("\nConclusion: stack arrays are fast but inflexible.\n");
    printf("The heap (malloc/calloc/realloc) lets us allocate\n");
    printf("exactly what we need, when we need it.\n");

    return EXIT_SUCCESS;
}
/*
 * Thinking in C:
 * Stack = fast, fixed at compile time, limited in size (~1-8 MB typical).
 * Heap = slower to allocate, but can grow and is only limited by RAM.
 * The first step to using dynamic memory is realising you NEED it.
 */
