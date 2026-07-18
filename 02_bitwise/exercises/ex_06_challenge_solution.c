/*
 * Exercise 06 — Bitwise Calculator (Challenge) — SOLUTION
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_bits(unsigned int n)
{
    for (int i = 31; i >= 0; i--) {
        putchar((n >> i) & 1 ? '1' : '0');
        if (i > 0 && i % 8 == 0)
            putchar(' ');
    }
}

/* Forward declaration for the operator-parsing helper */
static int parse_expression(const char *buf, unsigned int *a,
                            char op[3], unsigned int *b);

int main(void)
{
    char buf[64];

    printf("=== Bitwise Calculator ===\n");
    printf("Operators: & | ^ << >>\n");
    printf("Enter 'q' to quit.\n\n");

    while (1) {
        printf("Enter expression: ");
        if (fgets(buf, sizeof buf, stdin) == NULL)
            break;

        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] != '\n') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        } else if (len > 0) {
            buf[len - 1] = '\0';
        }

        if (buf[0] == 'q' && buf[1] == '\0')
            break;

        unsigned int a, b, result;
        char op[3] = {0};

        if (!parse_expression(buf, &a, op, &b)) {
            printf("Invalid format. Use: number operator number\n");
            continue;
        }

        if (strcmp(op, "&") == 0)
            result = a & b;
        else if (strcmp(op, "|") == 0)
            result = a | b;
        else if (strcmp(op, "^") == 0)
            result = a ^ b;
        else if (strcmp(op, "<<") == 0)
            result = a << b;
        else if (strcmp(op, ">>") == 0)
            result = a >> b;
        else {
            printf("Unknown operator '%s'. Use & | ^ << >>\n", op);
            continue;
        }

        printf("%-10u =  ", a);
        print_bits(a);
        printf("\n");
        printf("%-10u =  ", b);
        print_bits(b);
        printf("\n");
        printf("%u %s %u = %u =  ", a, op, b, result);
        print_bits(result);
        printf("\n\n");
    }

    printf("Goodbye!\n");
    return EXIT_SUCCESS;
}

/* Parse "number [operator] number" from buf using strtol + manual scanning.
 * Returns 1 on success, 0 on failure.  Operator can be 1 or 2 chars
 * (& | ^ << >>) and is NUL-terminated as a string in op[3]. */
static int parse_expression(const char *buf, unsigned int *a,
                            char op[3], unsigned int *b)
{
    char *p, *end;
    errno = 0;

    /* First number */
    unsigned long tmp = strtoul(buf, &end, 10);
    if (end == buf || errno == ERANGE)
        return 0;
    *a = (unsigned int)tmp;

    /* Skip whitespace between number and operator */
    p = end;
    while (*p == ' ' || *p == '\t')
        p++;

    /* Read operator (1 or 2 non-space, non-digit characters) */
    int op_len = 0;
    while (*p && *p != ' ' && *p != '\t' && !(*p >= '0' && *p <= '9')
           && op_len < 2) {
        op[op_len++] = *p;
        p++;
    }
    op[op_len] = '\0';
    if (op_len == 0)
        return 0;

    /* Skip whitespace between operator and second number */
    while (*p == ' ' || *p == '\t')
        p++;

    /* Second number */
    errno = 0;
    tmp = strtoul(p, &end, 10);
    if (end == p || errno == ERANGE)
        return 0;
    *b = (unsigned int)tmp;

    /* Ensure no trailing garbage */
    while (*end == ' ' || *end == '\t')
        end++;
    if (*end != '\0')
        return 0;

    return 1;
}
