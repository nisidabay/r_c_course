/* wc-lite — count lines, words, bytes in a file with String_Slice */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    const char *data;
    size_t len;
} String_Slice;

static String_Slice slice_from_cstring(const char *s) {
    String_Slice sl = { s, strlen(s) };
    return sl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    char buf[8192];
    long lines = 0, words = 0, bytes = 0;
    int in_word = 0;

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        String_Slice line = slice_from_cstring(buf);
        bytes += (long)line.len;
        lines++;

        for (size_t i = 0; i < line.len; i++) {
            if (isspace((unsigned char)line.data[i])) {
                in_word = 0;
            } else if (!in_word) {
                in_word = 1;
                words++;
            }
        }
    }

    if (ferror(fp)) {
        perror("fgets");
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);
    printf("%ld %ld %ld %s\n", lines, words, bytes, argv[1]);
    return EXIT_SUCCESS;
}
