/*
 * Exercise 04 — Toggle a bit — SOLUTION
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int toggle_bit(unsigned int n, int i)
{
    return n ^ (1U << i);
}

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

    printf("Enter a number: ");
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return EXIT_FAILURE;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

    char *endptr;
    unsigned long val = strtoul(buf, &endptr, 10);
    if (endptr == buf || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    unsigned int n = (unsigned int)val;

    printf("%u in binary: ", n);
    print_bits(n);
    printf("\n");

    printf("Enter bit to toggle (0-31): ");
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return EXIT_FAILURE;

    len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

    long pos = strtol(buf, &endptr, 10);
    if (endptr == buf || *endptr != '\0' || pos < 0 || pos > 31) {
        fprintf(stderr, "Invalid position\n");
        return EXIT_FAILURE;
    }

    unsigned int result = toggle_bit(n, (int)pos);
    printf("After toggle:   ");
    print_bits(result);
    printf(" (%u)\n", result);

    /* Toggle back to show XOR reversibility */
    result = toggle_bit(result, (int)pos);
    printf("Toggle again:   ");
    print_bits(result);
    printf(" (%u)\n", result);

    return EXIT_SUCCESS;
}
