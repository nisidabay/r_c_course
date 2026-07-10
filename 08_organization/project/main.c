/* todo — multi-file task manager (unity build) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.c"
#include "storage.c"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <add|list|done|help> [args]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "list") == 0) {
        todo_list();
    } else if (strcmp(argv[1], "add") == 0 && argc == 3) {
        todo_add(argv[2]);
    } else if (strcmp(argv[1], "done") == 0 && argc == 3) {
        int id = atoi(argv[2]);
        todo_done(id);
    } else {
        todo_help();
    }

    return EXIT_SUCCESS;
}
