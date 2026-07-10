/* grep-lite — substring search in command-line arguments */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <pattern> [file...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pattern = argv[1];
    char line[4096];
    int matched = 0;

    if (argc == 2) {
        /* Read from stdin */
        while (fgets(line, sizeof(line), stdin) != NULL) {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }
            if (strstr(line, pattern) != NULL) {
                puts(line);
                matched = 1;
            }
        }
    } else {
        for (int i = 2; i < argc; i++) {
            if (strstr(argv[i], pattern) != NULL) {
                puts(argv[i]);
                matched = 1;
            }
        }
    }

    return matched ? EXIT_SUCCESS : EXIT_FAILURE;
}
