/*
 * How do I use a unity build?
 *
 * A unity build merges all .c files into a single translation unit
 * via a single "unity" .c file that #includes all sources. This
 * avoids separate compilation overhead and enables cross-module
 * inlining at the cost of full rebuilds on any change.
 *
 * This file demonstrates the approach: everything lives in one
 * compilation unit, with #include to show the pattern.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- module: player ---- */

typedef struct {
    char name[64];
    int  level;
    int  hp;
} Player;

static int player_init(Player *p, const char *name, int level)
{
    if (p == NULL || name == NULL)
        return -1;

    size_t len = strlen(name);
    if (len >= sizeof(p->name))
        return -1;

    snprintf(p->name, sizeof(p->name), "%s", name);
    p->level = level;
    p->hp    = 100 + level * 10;
    return 0;
}

static void player_print(const Player *p)
{
    if (p == NULL) return;
    printf("Player {%s, lv %d, hp %d}\n", p->name, p->level, p->hp);
}

/* ---- module: game ---- */

static int game_run(void)
{
    Player hero;
    if (player_init(&hero, "Aria", 5) != 0)
        return EXIT_FAILURE;

    player_print(&hero);
    return EXIT_SUCCESS;
}

/* ---- unity entry point ---- */
/* In a real unity build this file would #include "player.c"
 * and #include "game.c". Here we inline everything above. */

int main(void)
{
    if (game_run() != EXIT_SUCCESS)
    {
        fprintf(stderr, "Game failed to start.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* Thinking in C: A unity build merges all modules into one .c file
 * (#include everything) so the compiler sees the full program at once.
 * Great for small projects; terrible for large ones due to rebuild cost. */


// 💡 Thinking in C:
// Unity build: include all .c files from one main.c. Fast compilation, no headers needed.
