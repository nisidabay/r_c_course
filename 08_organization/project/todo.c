/* todo.c — task operations */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int save_task(const char *text, int done);
extern int mark_done(int id);

static int next_id(void) {
    static int id = 1;
    return id++;
}

void todo_add(const char *text) {
    int id = next_id();
    if (save_task(text, 0)) {
        printf("Added task #%d: %s\n", id, text);
    } else {
        fprintf(stderr, "error: could not save task\n");
    }
}

void todo_list(void) {
    printf("No tasks yet (storage not implemented).\n");
}

void todo_done(int id) {
    if (mark_done(id)) {
        printf("Task #%d marked as done.\n", id);
    } else {
        fprintf(stderr, "error: task #%d not found\n", id);
    }
}

void todo_help(void) {
    printf("Usage:\n");
    printf("  %s add <text>   — add a task\n", "todo");
    printf("  %s list         — list all tasks\n", "todo");
    printf("  %s done <id>    — mark task as done\n", "todo");
}
