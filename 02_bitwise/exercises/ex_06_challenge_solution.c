/*
 * Exercise 06 — Bitwise Calculator (Challenge) — SOLUTION
 */

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
        char op;
        int n = sscanf(buf, "%u %c %u", &a, &op, &b);
        if (n != 3) {
            printf("Invalid format. Use: number operator number\n");
            continue;
        }

        switch (op) {
        case '&':  result = a & b;  break;
        case '|':  result = a | b;  break;
        case '^':  result = a ^ b;  break;
        case '<':
            if (buf[0] == '<') {   /* already consumed first < */
                /* re-parse: the sscanf read '<' as op, now we need '<<' */
                printf("Use format: number << number (no spaces between <<)\n");
                continue;
            }
            /* fallback: re-parse with %u %%c %u only catches single char */
            /* Actually let's handle << properly */
            {
                char op1, op2;
                sscanf(buf, "%u %c%c %u", &a, &op1, &op2, &b);
                if (op1 == '<' && op2 == '<')
                    result = a << b;
                else {
                    printf("Unknown operator\n");
                    continue;
                }
            }
            break;
        case '>':
            {
                char op1, op2;
                sscanf(buf, "%u %c%c %u", &a, &op1, &op2, &b);
                if (op1 == '>' && op2 == '>')
                    result = a >> b;
                else {
                    printf("Unknown operator\n");
                    continue;
                }
            }
            break;
        default:
            printf("Unknown operator '%c'. Use & | ^ << >>\n", op);
            continue;
        }

        printf("%-10u =  ", a);
        print_bits(a);
        printf("\n");
        printf("%-10u =  ", b);
        print_bits(b);
        printf("\n");
        printf("%u %c %u = %u =  ", a, op, b, result);
        print_bits(result);
        printf("\n\n");
    }

    printf("Goodbye!\n");
    return EXIT_SUCCESS;
}
