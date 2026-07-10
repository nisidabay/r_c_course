/* divider — command-line integer math with safe parsing */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static long parse_long(const char *s) {
    char *end = NULL;
    errno = 0;
    long val = strtol(s, &end, 10);
    if (errno != 0 || *end != '\0' || end == s) {
        fprintf(stderr, "error: '%s' is not a valid integer\n", s);
        exit(EXIT_FAILURE);
    }
    return val;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s <a> <op> <b>\n", argv[0]);
        fprintf(stderr, "  op: + - x / %%\n");
        return EXIT_FAILURE;
    }

    long a = parse_long(argv[1]);
    const char *op = argv[2];
    long b = parse_long(argv[3]);
    long result = 0;

    if (strcmp(op, "+") == 0) {
        result = a + b;
    } else if (strcmp(op, "-") == 0) {
        result = a - b;
    } else if (strcmp(op, "x") == 0) {
        result = a * b;
    } else if (strcmp(op, "/") == 0) {
        if (b == 0) {
            fprintf(stderr, "error: division by zero\n");
            return EXIT_FAILURE;
        }
        result = a / b;
    } else if (strcmp(op, "%") == 0) {
        if (b == 0) {
            fprintf(stderr, "error: modulo by zero\n");
            return EXIT_FAILURE;
        }
        result = a % b;
    } else {
        fprintf(stderr, "error: unknown operator '%s'\n", op);
        return EXIT_FAILURE;
    }

    printf("%ld %s %ld = %ld\n", a, op, b, result);
    return EXIT_SUCCESS;
}
