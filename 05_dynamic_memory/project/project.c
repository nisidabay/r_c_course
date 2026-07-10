/* uniq — deduplicate lines from stdin using a dynamic array */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char **lines = NULL;
static size_t count = 0;
static size_t capacity = 0;

static void add_line(const char *s) {
    if (count >= capacity) {
        size_t new_cap = capacity == 0 ? 8 : capacity * 2;
        char **new_lines = realloc(lines, new_cap * sizeof(char *));
        if (new_lines == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        lines = new_lines;
        capacity = new_cap;
    }

    lines[count] = malloc(strlen(s) + 1);
    if (lines[count] == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(lines[count], s);
    count++;
}

static int seen_before(const char *s) {
    for (size_t i = 0; i < count; i++) {
        if (strcmp(lines[i], s) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    char buf[4096];

    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }

        if (!seen_before(buf)) {
            add_line(buf);
        }
    }

    for (size_t i = 0; i < count; i++) {
        puts(lines[i]);
        free(lines[i]);
    }
    free(lines);

    return EXIT_SUCCESS;
}
