/*
 * ex_04_strtok_r_solution.c
 * Group 10 — Advanced
 * Exercise 04: reentrant tokenisation with strtok_r — SOLUTION
 */

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *dup_str(const char *s) {
    size_t len = strlen(s);
    char  *d   = malloc(len + 1);
    if (!d) return NULL;
    memcpy(d, s, len + 1);
    return d;
}

static char **tokenise(const char *str, const char *delim, size_t *out_count) {
    char *work = dup_str(str);
    if (!work) return NULL;

    size_t  cap    = 4;
    size_t  count  = 0;
    char  **tokens = malloc(cap * sizeof(char *));
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
    const char data[] = "name=Alice,role=engineer,dept=infra\n"
                        "name=Bob,role=designer,dept=creative\n";

    size_t line_count = 0;
    char **lines = tokenise(data, "\n", &line_count);

    if (!lines) {
        fprintf(stderr, "tokenisation failed\n");
        return 1;
    }

    printf("Parsed %zu lines:\n", line_count);

    for (size_t i = 0; i < line_count; i++) {
        printf("  Line %zu: ", i + 1);

        size_t field_count = 0;
        char **fields = tokenise(lines[i], ",", &field_count);

        for (size_t j = 0; j < field_count; j++) {
            printf("[%s]%s", fields[j],
                   (j + 1 < field_count) ? " " : "");
            free(fields[j]);
        }
        free(fields);
        printf("\n");
    }

    for (size_t i = 0; i < line_count; i++) free(lines[i]);
    free(lines);
    return 0;
}
