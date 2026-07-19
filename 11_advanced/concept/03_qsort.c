/*
 * File:  03_qsort.c
 * Group: 10 — Paradigm Shift: qsort & Callbacks
 *
 * Concept: qsort with a function pointer callback (comparator)
 *
 * The comparator signature is:
 *     int cmp(const void *a, const void *b);
 *
 * Key gotcha: the const void* must be CAST to the actual element type
 * before dereferencing.  This is the trickiest part for newcomers.
 *
 * Shows:
 *   - qsort(arr, n, elem_size, comparator)
 *   - The const void* → int* cast inside the comparator
 *   - Struct sorting (combining group 01 structs with group 04 arrays)
 *   - Dynamic memory (group 09) — we sort a heap-allocated array
 *   - snprintf for all string building
 *
 * Build:  gcc -std=c11 -Wall -Wextra -pedantic 03_qsort.c -o 03_qsort
 * Run:    ./03_qsort
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- a struct to sort (group 01: structs) ---------- */
typedef struct {
    char  name[32];
    int   score;
} Player;

/* ---------- comparator: sort players by score ascending ---------- */
int compare_by_score(const void *a, const void *b) {
    /* cast from void* to the actual type — the tricky part */
    const Player *pa = (const Player *)a;
    const Player *pb = (const Player *)b;

    if (pa->score > pb->score) return +1;
    if (pa->score < pb->score) return -1;
    return 0;
}

/* ---------- comparator: sort players by name alphabetically ---------- */
int compare_by_name(const void *a, const void *b) {
    const Player *pa = (const Player *)a;
    const Player *pb = (const Player *)b;
    /* strcmp is fine here — we're comparing existing strings, not copying */
    return strcmp(pa->name, pb->name);
}

int main(void) {
    /* dynamic array of players (group 09: dynamic memory) */
    size_t n = 5;
    Player *players = malloc(n * sizeof(Player));
    if (!players) {
        fprintf(stderr, "malloc failed\n");
        return EXIT_FAILURE;
    }

    /* initialise (group 07: safe string building via snprintf) */
    snprintf(players[0].name, sizeof players[0].name, "Zara");
    players[0].score = 88;

    snprintf(players[1].name, sizeof players[1].name, "Alex");
    players[1].score = 95;

    snprintf(players[2].name, sizeof players[2].name, "Maya");
    players[2].score = 72;

    snprintf(players[3].name, sizeof players[3].name, "Carlos");
    players[3].score = 95;

    snprintf(players[4].name, sizeof players[4].name, "Leila");
    players[4].score = 81;

    char buf[256];

    /* --- sort by score --- */
    qsort(players, n, sizeof(Player), compare_by_score);

    snprintf(buf, sizeof buf, "By score:");
    for (size_t i = 0; i < n; i++) {
        size_t off = strlen(buf);
        snprintf(buf + off, sizeof buf - off,
                 "  %s(%d)", players[i].name, players[i].score);
    }
    printf("%s\n", buf);

    /* --- sort by name --- */
    qsort(players, n, sizeof(Player), compare_by_name);

    snprintf(buf, sizeof buf, "By name: ");
    for (size_t i = 0; i < n; i++) {
        size_t off = strlen(buf);
        snprintf(buf + off, sizeof buf - off,
                 "  %s(%d)", players[i].name, players[i].score);
    }
    printf("%s\n", buf);

    free(players);
    return EXIT_SUCCESS;
}

/*
 * Thinking in C — Group 10
 *
 * qsort doesn't know your types, so it uses void* — you teach it how to
 * compare by writing a callback.  The const void* cast is the price of
 * genericity: you must tell the compiler "I know what this really is."
 * Once you internalise that pattern, you unlock reusable algorithms that
 * work on any struct, any ordering, any dimension.
 */
