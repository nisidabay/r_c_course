/* calc — safe integer arithmetic from command line */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static long parse_long(const char *s, const char *name) {
    char *end = NULL;
    errno = 0;
    long val = strtol(s, &end, 10);
    if (errno != 0 || *end != '\0' || end == s) {
        fprintf(stderr, "error: %s '%s' is not a valid integer\n", name, s);
        exit(EXIT_FAILURE);
    }
    return val;
}

static long do_op(long a, const char *op, long b) {
    if (strcmp(op, "+") == 0) return a + b;
    if (strcmp(op, "-") == 0) return a - b;
    if (strcmp(op, "x") == 0) return a * b;
    if (strcmp(op, "/") == 0) {
        if (b == 0) { fprintf(stderr, "error: division by zero\n"); exit(EXIT_FAILURE); }
        return a / b;
    }
    fprintf(stderr, "error: unknown operator '%s'\n", op);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s <a> <op> <b>\n", argv[0]);
        fprintf(stderr, "  op: + - x /\n");
        return EXIT_FAILURE;
    }

    long a = parse_long(argv[1], "first operand");
    long b = parse_long(argv[3], "second operand");
    long result = do_op(a, argv[2], b);

    printf("%ld %s %ld = %ld\n", a, argv[2], b, result);
    return EXIT_SUCCESS;
}
