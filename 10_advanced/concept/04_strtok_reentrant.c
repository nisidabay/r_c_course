/*
 * File:  04_strtok_reentrant.c
 * Group: 10 — Paradigm Shift: Reentrant Tokenisation
 *
 * Concept: strtok_r — the thread-safe, reentrant version of strtok
 *
 * strtok_r(str, delim, &saveptr) stores the parser position in a
 * caller-provided saveptr so multiple tokenisation loops don't interfere.
 * This requires _POSIX_C_SOURCE (POSIX extension, not ISO C alone).
 *
 * Shows:
 *   - strtok_r with a saveptr for nested / sequential tokenisation
 *   - Dynamic memory (group 09) to collect tokens into an array
 *   - File I/O (group 08) — reads a config-like string from a buffer
 *   - snprintf for all string building (no sprintf)
 *   - Manual strdup replacement to avoid POSIX dependency hell
 *
 * Build:  gcc -std=c11 -Wall -Wextra -pedantic 04_strtok_reentrant.c -o 04_strtok_reentrant
 * Run:    ./04_strtok_reentrant
 *
 * NOTE: strtok_r is a POSIX function.  We define _POSIX_C_SOURCE before
 *       ANY includes to expose it even under -std=c11 (strict mode).
 *       On systems without strtok_r, see the fallback note at the bottom.
 */

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- safe strdup replacement (avoids POSIX strdup) ---------- */
static char *dup_str(const char *s) {
    size_t len = strlen(s);
    char  *d   = malloc(len + 1);
    if (!d) return NULL;
    memcpy(d, s, len + 1);
    return d;
}

/* ---------- tokenise into a dynamic array (group 09) ---------- */
static char **tokenise(const char *str, const char *delim, size_t *out_count) {
    char *work = dup_str(str);   /* strtok_r modifies its input */
    if (!work) return NULL;

    size_t  cap     = 8;
    size_t  count   = 0;
    char  **tokens  = malloc(cap * sizeof(char *));
    if (!tokens) { free(work); return NULL; }

    char   *saveptr = NULL;
    char   *token   = strtok_r(work, delim, &saveptr);

    while (token) {
        if (count >= cap) {
            cap *= 2;
            char **tmp = realloc(tokens, cap * sizeof(char *));
            if (!tmp) {
                for (size_t i = 0; i < count; i++) free(tokens[i]);
                free(tokens); free(work);
                return NULL;
            }
            tokens = tmp;
        }
        tokens[count] = dup_str(token);
        if (!tokens[count]) {
            for (size_t i = 0; i < count; i++) free(tokens[i]);
            free(tokens); free(work);
            return NULL;
        }
        count++;
        token = strtok_r(NULL, delim, &saveptr);
    }

    free(work);
    *out_count = count;
    return tokens;
}

int main(void) {
    /*
     * Simulates reading config from a file (group 08 concept).
     * A real program would fopen + fread into this buffer.
     */
    const char data[] =
        "host=server01|port=9090|timeout=30|retries=3\n"
        "host=server02|port=9091|timeout=15|retries=5\n";

    size_t line_count = 0;
    char **lines = tokenise(data, "\n", &line_count);

    if (!lines) {
        fprintf(stderr, "tokenisation failed\n");
        return EXIT_FAILURE;
    }

    char buf[256];

    for (size_t i = 0; i < line_count; i++) {
        snprintf(buf, sizeof buf, "Line %zu: ", i + 1);

        /* nested tokenisation — each line gets its own saveptr */
        size_t pair_count = 0;
        char  **pairs = tokenise(lines[i], "|", &pair_count);

        for (size_t j = 0; j < pair_count; j++) {
            size_t off = strlen(buf);
            snprintf(buf + off, sizeof buf - off, "[%s] ", pairs[j]);
            free(pairs[j]);
        }
        free(pairs);
        printf("%s\n", buf);
    }

    for (size_t i = 0; i < line_count; i++) free(lines[i]);
    free(lines);
    return EXIT_SUCCESS;
}

/*
 * Fallback / non-POSIX note:
 * Without strtok_r you can write a simple custom tokeniser that tracks
 * position via a caller-owned index — the same interface as strtok_r but
 * using s = strpbrk(s, delim) / strcspn loops instead of relying on a
 * hidden static pointer.
 */

/*
 * Thinking in C — Group 10
 *
 * strtok's hidden static state makes it non-reentrant — one loop breaks
 * another.  strtok_r fixes this by making YOU hold the state via saveptr.
 * The principle: never hide mutable state behind an API when the caller
 * could own it.  This pattern reappears in async contexts, generators,
 * and state machines throughout all of systems programming.
 */
