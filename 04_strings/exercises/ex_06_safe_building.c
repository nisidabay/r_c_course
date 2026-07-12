/*
 * Exercise 06: Safe string construction when you DO need to copy
 *
 * Concept: Zero-copy slicing is great when you can keep the original
 *          memory alive. But sometimes you NEED a real copy:
 *          - constructing formatted output (use snprintf, NOT sprintf)
 *          - duplicating strings (use strdup with NULL check)
 *
 * Fill in the blanks to complete the program.
 *
 * NOTE: strdup requires _POSIX_C_SOURCE 200809L — we define it below.
 *
 * Note: Exercises 03+ use size_t (from <stddef.h>).
 *
 * Safe C Standard: no strcpy/strcat/sprintf/scanf/atoi/atof.
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_06_safe_building.c -o ex_06_safe_building
 */

#define _POSIX_C_SOURCE 200809L   /* for strdup (POSIX.1-2008) */

#include <stddef.h>   // size_t is an unsigned integer type from <stddef.h>, used for sizes and indices
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    /* --- snprintf: safe formatted construction --- */
    char greeting[64];
    char *name = "Alice";
    int count = 42;

    /* snprintf writes AT MOST sizeof(greeting)-1 chars, then always null-terminates.
     * Returns how many characters it WOULD have written (excluding \0) if space were unlimited.
     * If return >= sizeof(buf), output was truncated — you can detect it. */
    int needed = snprintf(greeting, sizeof(greeting),
                          "Hello %s, you have %d messages.", name, count); // FIX ME

    printf("snprintf result:\n");
    printf("  Needed: %d characters (would need %zu-byte buffer for full output)\n",
           needed, (size_t)needed + 1);
    printf("  Wrote:  \"%s\"\n", greeting);

    if ((size_t)needed >= sizeof(greeting)) {
        printf("  (Output was TRUNCATED — buffer too small)\n");
    }

    /* --- strdup: safe duplication with NULL check --- */
    char *original = "This text needs to be copied to a new location.";
    char *copy = strdup(original); // FIX ME

    /* strdup returns NULL if malloc fails — ALWAYS check */
    if (!copy) {
        perror("strdup");
        return 1;
    }

    printf("\nstrdup result:\n");
    printf("  Original: \"%s\"  (at %p)\n", original, (void *)original);
    printf("  Copy:     \"%s\"  (at %p)\n", copy, (void *)copy);
    printf("  Different addresses -> copy IS a real, independent allocation.\n");

    /* Modify the copy — safe because it's our own memory */
    copy[0] = 't';
    printf("  Modified copy: \"%s\"  (original unchanged)\n", copy);

    /* Always free what strdup gave you */
    free(copy);

    /* --- snprintf for path construction --- */
    char path[256];
    char *dir  = "/home/alice";
    char *file = "documents/report.txt";

    /* Build the path: dir/file */
    snprintf(path, sizeof(path), "%s/%s", dir, file); // FIX ME
    printf("\nConstructed path: \"%s\"\n", path);

    printf("\nSafe building rules:\n");
    printf("  1. snprintf(buf, sizeof(buf), ...) — always bound the output\n");
    printf("  2. strdup(src) — but ALWAYS check for NULL return\n");
    printf("  3. free() what you strdup() — ownership is now yours\n");

    return 0;
}
